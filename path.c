/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:23:13 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 10:02:33 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(void)
{
	t_env	*env;
	char	*tmp;

	env = *env_func();
	tmp = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 4) == 0)
		{
			tmp = env->value;
			break ;
		}
		env = env->next;
	}
	return (tmp);
}

char	**split_path(void)
{
	char	*path;
	char	**splited_path;

	path = find_path();
	if (path == NULL)
		return (NULL);
	splited_path = ft_split(path, ':');
	return (splited_path);
}

int	is_builtin(t_token_exc **token_list)
{
	if ((ft_strncmp((*token_list)->cmd, "echo", 4) == 0)
		|| (ft_strncmp((*token_list)->cmd, "cd", 2) == 0)
		|| (ft_strncmp((*token_list)->cmd, "pwd", 4) == 0)
		|| (ft_strncmp((*token_list)->cmd, "export", 6) == 0)
		|| (ft_strncmp((*token_list)->cmd, "unset", 5) == 0)
		|| (ft_strncmp((*token_list)->cmd, "env", 3) == 0)
		|| (ft_strncmp((*token_list)->cmd, "exit", 4) == 0))
		return (0); // builtin
	else
		return (1);
}

int	check_first_cmd(t_token_exc *token_list)
{
	char	*s;

	s = token_list->cmd;
	if (ft_strncmp(s, ">", 1) == 0 || ft_strncmp(s, ">>", 2) == 0
		|| ft_strncmp(s, "<", 1) == 0 || ft_strncmp(s, "<<", 2) == 0
		|| ft_strncmp(s, "./minishell", ft_strlen("./minishell")) == 0)
		return (0);
	else
		return (1);
}

void print_cmd_error(const char *cmd)
{
    struct stat st;

    if (!cmd || cmd[0] == 0)
        return; // Don't print anything for empty

    if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
        printf("minishell: %s: Is a directory\n", cmd);
	else
        printf("%s: command not found\n", cmd);
}


void	path(t_token_exc **token_list)
{
    char    **splited_path;
    char    *new_cmd;
    char    *tmp;
    int     flag;
    int     i;

    splited_path = split_path();
    flag = 0;
    if (!splited_path)
        return ;
    (*token_list)->cmd_path = NULL;
    new_cmd = ft_strjoin("/", (*token_list)->cmd);
    for (i = 0; splited_path[i]; i++)
    {
        tmp = ft_strjoin(splited_path[i], new_cmd);
        if (access(tmp, F_OK) == 0)
        {
            flag = 1;
            (*token_list)->cmd_path = tmp;
            break;
        }
        free(tmp);
    }
    free(new_cmd);
    for (i = 0; splited_path[i]; i++)
        free(splited_path[i]);
    free(splited_path);
	if (flag == 0 && check_first_cmd(*token_list) == 1)
	{
		if (!(*token_list)->cmd || (*token_list)->cmd[0] == '\0')
        	return;
		print_cmd_error((*token_list)->cmd);
		return ;
	}
	// printf("path's command --> %s\n", (*token_list)->cmd_path);
}
