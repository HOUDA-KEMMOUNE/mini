/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 11:06:14 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/30 11:53:01 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_cd_error(const char *path)
{
	struct stat st;

	if (access(path, F_OK) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
	else if (access(path, X_OK) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
	}
	else if (stat(path, &st) == 0 && !S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		ft_putstr_fd(": error\n", 2);
	}
}


void update_env(t_env *env, char *key, char *new_value)
{
    while (env)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            free(env->value);
            env->value = ft_strdup(new_value);
            return;
        }
        env = env->next;
    }

}

int builtin_cd(char **args, t_env *env)
{
	char *target = NULL;
	char cwd[4096];

	// Save current directory to OLDPWD
	if (!getcwd(cwd, sizeof(cwd)))
	{
		perror("getcwd");
		return 1;
	}
	update_env(env, "OLDPWD", cwd);  // update OLDPWD

	// Determine target directory
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		target = get_env_value(env, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value(env, "OLDPWD");
		if (target)
			printf("%s\n", target);  // cd - prints path
	}
	else
		target = args[1];

	// Handle missing HOME or OLDPWD
	if (!target)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": Not set\n", 2);
		return 1;
	}

	// Attempt to change directory
	if (chdir(target) != 0)
	{
		print_cd_error(target);
		return 1;
	}

	// Update PWD
	if (getcwd(cwd, sizeof(cwd)))
		update_env(env, "PWD", cwd);

	return 0;
}
