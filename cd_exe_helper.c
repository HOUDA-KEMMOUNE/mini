/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 12:14:29 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/27 12:14:32 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace_only(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace((unsigned char)str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	cd_dash_setup_env(t_env **env_list)
{
	char	cwd[4096];
	char	*current_pwd;

	if (getcwd(cwd, sizeof(cwd)))
		update_env(*env_list, "OLDPWD", cwd);
	else
	{
		current_pwd = get_env_value(*env_list, "PWD");
		if (current_pwd)
			update_env(*env_list, "OLDPWD", current_pwd);
	}
	return (0);
}

static int	cd_dash_change_dir(const char *oldpwd, t_env **env_list)
{
	char		cwd[4096];
	struct stat	st;

	if (chdir(oldpwd) != 0)
	{
		if (access(oldpwd, F_OK) != 0)
			return (print_cd_error(oldpwd, 2), 1);
		if (access(oldpwd, X_OK) != 0)
			return (print_cd_error(oldpwd, 3), 1);
		if (stat(oldpwd, &st) == 0 && !S_ISDIR(st.st_mode))
			return (print_cd_error(oldpwd, 4), 1);
		return (print_cd_error(oldpwd, 6), 1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		update_env(*env_list, "PWD", cwd);
	return (0);
}

int	handle_cd_dash(t_env **env_list)
{
	char	*oldpwd;

	oldpwd = get_env_value(*env_list, "OLDPWD");
	if (!oldpwd || !*oldpwd)
		return (print_cd_error("OLDPWD not set", 5), 1);
	write(1, oldpwd, ft_strlen(oldpwd));
	write(1, "\n", 1);
	cd_dash_setup_env(env_list);
	return (cd_dash_change_dir(oldpwd, env_list));
}
