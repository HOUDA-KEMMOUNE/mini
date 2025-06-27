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

int	handle_cd_dash(t_env **env_list)
{
	char		cwd[4096];
	char		*oldpwd;
	struct stat	st;

	oldpwd = get_env_value(*env_list, "OLDPWD");
	if (!oldpwd || !*oldpwd)
		return (print_cd_error("OLDPWD not set", 5), 1);
	write(1, oldpwd, strlen(oldpwd));
	write(1, "\n", 1);
	if (!getcwd(cwd, sizeof(cwd)))
		return (print_cd_error(oldpwd, 6), 1);
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
	update_env(*env_list, "OLDPWD", cwd);
	if (getcwd(cwd, sizeof(cwd)))
		update_env(*env_list, "PWD", cwd);
	return (0);
}

char	*expand_tilde(const char *path, t_env *env_list)
{
	char	*home;
	char	*expanded_path;
	size_t	home_len;
	size_t	path_len;

	expanded_path = NULL;
	home = get_env_value(env_list, "HOME");
	if (!home)
		return (NULL);
	home_len = strlen(home);
	path_len = strlen(path);
	expanded_path = malloc(home_len + path_len);
	if (!expanded_path)
		return (NULL);
	strcpy(expanded_path, home);
	strcat(expanded_path, path + 1);
	return (expanded_path);
}

int	handle_basic_cd(const char *path, t_env **env_list)
{
	char		cwd[4096];
	struct stat	st;

	if (!getcwd(cwd, sizeof(cwd)))
		return (print_cd_error(path, 6), 1);
	update_env(*env_list, "OLDPWD", cwd);
	if (chdir(path) != 0)
	{
		if (access(path, F_OK) != 0)
			return (print_cd_error(path, 2), 1);
		if (access(path, X_OK) != 0)
			return (print_cd_error(path, 3), 1);
		if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
			return (print_cd_error(path, 4), 1);
		return (print_cd_error(path, 6), 1);
	}
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
