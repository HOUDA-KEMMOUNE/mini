/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 11:09:20 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/07/01 11:10:16 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_oldpwd(t_env **env_list)
{
	char	cwd[4096];
	char	*old_pwd;

	if (getcwd(cwd, sizeof(cwd)))
		update_env(*env_list, "OLDPWD", cwd);
	else
	{
		old_pwd = get_env_value(*env_list, "PWD");
		if (old_pwd)
			update_env(*env_list, "OLDPWD", old_pwd);
	}
	return (0);
}

static int	handle_chdir_error(const char *path)
{
	struct stat	st;

	if (access(path, F_OK) != 0)
		return (print_cd_error(path, 2), 1);
	if (access(path, X_OK) != 0)
		return (print_cd_error(path, 3), 1);
	if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
		return (print_cd_error(path, 4), 1);
	return (print_cd_error(path, 6), 1);
}

int	handle_basic_cd(const char *path, t_env **env_list)
{
	char	cwd[4096];

	update_oldpwd(env_list);
	if (chdir(path) != 0)
		return (handle_chdir_error(path));
	if (getcwd(cwd, sizeof(cwd)))
		update_env(*env_list, "PWD", cwd);
	return (0);
}

char	*determine_path(t_token *tokens, t_env *env_list, char **to_free)
{
	char	*path;

	path = tokens->next->value;
	if (is_whitespace_only(path))
	{
		path = get_env_value(env_list, "HOME");
		if (!path)
		{
			print_cd_error("HOME not set", 5);
			return (NULL);
		}
	}
	if (path[0] == '~')
	{
		*to_free = expand_tilde(path, env_list);
		if (!*to_free)
		{
			print_cd_error("HOME not set", 5);
			return (NULL);
		}
		path = *to_free;
	}
	return (path);
}

int	cd(t_token *tokens, t_env **env_list)
{
	char	*path;
	char	*to_free;
	char	*home;
	int		result;

	to_free = NULL;
	if (!tokens)
		return (0);
	if (!tokens->next)
	{
		home = get_env_value(*env_list, "HOME");
		if (!home)
			return (print_cd_error("HOME not set", 5), 1);
		return (handle_basic_cd(home, env_list));
	}
	if (tokens->next->next)
		return (print_cd_error("cd", 1), 1);
	if (ft_strncmp(tokens->next->value, "-", 2) == 0)
		return (handle_cd_dash(env_list));
	path = determine_path(tokens, *env_list, &to_free);
	if (!path)
		return (1);
	result = handle_basic_cd(path, env_list);
	free(to_free);
	return (result);
}
