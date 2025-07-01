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

void	print_cd_error2(const char *arg, int error_type)
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

void	print_cd_error(const char *arg, int error_type)
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
