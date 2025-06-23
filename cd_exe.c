/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:06:14 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 19:10:17 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cd_error2(char *arg, int error_type)
{
	if (error_type == 4)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (error_type == 5)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Not set\n", 2);
	}
	else if (error_type == 6)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": error\n", 2);
	}
}

void	print_cd_error(char *arg, int error_type)
{
	if (error_type == 1)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	}
	else if (error_type == 2)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (error_type == 3)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	print_cd_error2(arg, error_type);
}

void	update_env(t_env *env, char *key, char *new_value)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_value);
			return ;
		}
		env = env->next;
	}
}

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
}

int	cd(t_token *tokens, t_env **env_list)
{
	char		cwd[4096];
	char		*path;
	char		*to_free;
	struct stat	st;
	int			i;
	int			is_whitespace_only;
	char		*oldpwd;
	char		*home;
	size_t		home_len;
	size_t		path_len;

	is_whitespace_only = 1;
	i = 0;
	to_free = NULL;
	if (!tokens || !tokens->next)
		return (0);
	path = tokens->next->value;
	while (path[i])
	{
		if (!ft_isspace((unsigned char)path[i]))
		{
			is_whitespace_only = 0;
			break ;
		}
		i++;
	}
	if (is_whitespace_only)
	{
		path = get_env_value(*env_list, "HOME");
		if (!path)
			return (print_cd_error("HOME not set", 5), 1);
	}
	if (tokens->next->next)
	{
		print_cd_error("cd", 1);
		return (1);
	}
	if (strcmp(path, "-") == 0)
	{
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
	if (path[0] == '~')
	{
		home = get_env_value(*env_list, "HOME");
		if (!home)
			return (print_cd_error("HOME not set", 5), 1);
		home_len = strlen(home);
		path_len = strlen(path);
		to_free = malloc(home_len + path_len);
		if (!to_free)
			return (print_cd_error("malloc", 6), 1);
		strcpy(to_free, home);
		strcat(to_free, path + 1);
		path = to_free;
	}
	if (!getcwd(cwd, sizeof(cwd)))
	{
		free(to_free);
		return (print_cd_error(path, 6), 1);
	}
	update_env(*env_list, "OLDPWD", cwd);
	if (chdir(path) != 0)
	{
		if (access(path, F_OK) != 0)
			return (print_cd_error(path, 2), free(to_free), 1);
		if (access(path, X_OK) != 0)
			return (print_cd_error(path, 3), free(to_free), 1);
		if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
			return (print_cd_error(path, 4), free(to_free), 1);
		free(to_free);
		return (print_cd_error(path, 6), 1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		update_env(*env_list, "PWD", cwd);
	free(to_free);
	return (0);
}
