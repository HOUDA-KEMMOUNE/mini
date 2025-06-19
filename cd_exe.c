/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:06:14 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/19 18:22:10 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void print_cd_error(const char *path)
// {
// 	struct stat st;

// 	if (access(path, F_OK) != 0)
// 	{
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		ft_putstr_fd((char *)path, 2);
// 		ft_putstr_fd(": No such file or directory\n", 2);
// 	}
// 	else if (access(path, X_OK) != 0)
// 	{
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		ft_putstr_fd((char *)path, 2);
// 		ft_putstr_fd(": Permission denied\n", 2);
// 	}
// 	else if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
// 	{
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		ft_putstr_fd((char *)path, 2);
// 		ft_putstr_fd(": Not a directory\n", 2);
// 	}
// 	else
// 	{
// 		ft_putstr_fd("minishell: cd: ", 2);
// 		ft_putstr_fd((char *)path, 2);
// 		ft_putstr_fd(": error\n", 2);
// 	}
// }
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
	else if (error_type == 4)
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
	int			is_whitespace_only;
	struct stat	st;

	(void)env_list;
	// No argument: do nothing (or change to home if that's your implementation for `cd` with no args)
	if (!tokens || !tokens->next)
		return (0);
	path = tokens->next->value;
	// Check if the path is an empty string or contains only whitespace
	is_whitespace_only = 1;
	for (int i = 0; path[i] != '\0'; i++)
	{
		if (!ft_isspace((unsigned char)path[i]))
		{
			is_whitespace_only = 0;
			break ;
		}
	}
	if (is_whitespace_only)
	{
		// If it's just whitespace, ignore it like normal cd
		return (0);
	}
	// Too many arguments: error
	if (tokens->next->next)
	{
		print_cd_error("cd", 1);
		return (1);
	}
	// Ignore '~' and '-' silently
	if (ft_strcmp(path, "~") == 0 || ft_strcmp(path, "-") == 0)
		return (0);
	// Save current directory
	if (!getcwd(cwd, sizeof(cwd)))
		return (print_cd_error(path, 6), 1);
	update_env(*env_list, "OLDPWD", cwd);
	// Try to change directory
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
	// Update new current directory
	if (getcwd(cwd, sizeof(cwd)))
		update_env(*env_list, "PWD", cwd);
	return (0);
}

// int cd(t_token *tokens, t_env *env)
// {
//     char cwd[4096];
//     char *path;

//     if (!getcwd(cwd, sizeof(cwd)))
//         return (print_cd_error("", 6), 1);
//     update_env(env, "OLDPWD", cwd);

//     if (tokens && tokens->next && tokens->next->next)
//         return (print_cd_error(NULL, 1), 1);

//     if (tokens && tokens->next)
//         path = tokens->next->value;
//     else
//     {
//         path = get_env_value(env, "HOME");
//         if (!path)
//             return (print_cd_error("HOME", 5), 1);
//     }

//     if (ft_strcmp(path, "-") == 0)
//     {
//         path = get_env_value(env, "OLDPWD");
//         if (!path)
//             return (print_cd_error("OLDPWD", 5), 1);
//         ft_putendl_fd(path, 1); // show the directory
//     }
//     else if (path[0] == '~')
//     {
//         char *home = get_env_value(env, "HOME");
//         if (!home)
//             return (print_cd_error("HOME", 5), 1);
//         path = ft_strjoin(home, path + 1);
//         // NOTE: free(path) if ft_strjoin allocates
//     }

//     if (chdir(path) != 0)
//     {
//         struct stat st;
//         if (access(path, F_OK) != 0)
//             return (print_cd_error(path, 2), 1);
//         if (access(path, X_OK) != 0)
//             return (print_cd_error(path, 3), 1);
//         if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
//             return (print_cd_error(path, 4), 1);
//         return (print_cd_error(path, 6), 1);
//     }

//     if (getcwd(cwd, sizeof(cwd)))
//         update_env(env, "PWD", cwd);

//     return (0);
// }
