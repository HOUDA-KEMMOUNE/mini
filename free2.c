/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 10:04:20 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 10:05:16 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_array(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

void	free_args(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_delimiter_array(t_token_exc *cmd)
{
	int	j;

	if (cmd->delimiter)
	{
		j = 0;
		while (j < cmd->count_heredoc)
		{
			if (cmd->delimiter[j])
				free(cmd->delimiter[j]);
			j++;
		}
		free(cmd->delimiter);
	}
}

void	free_heredoc_file_array(t_token_exc *cmd)
{
	int	j;

	if (cmd->heredoc_file)
	{
		j = 0;
		while (j < cmd->count_heredoc)
		{
			if (cmd->heredoc_file[j])
			{
				unlink(cmd->heredoc_file[j]);
				free(cmd->heredoc_file[j]);
			}
			j++;
		}
		free(cmd->heredoc_file);
	}
}

void	free_heredoc_arrays(t_token_exc *cmd)
{
	free_delimiter_array(cmd);
	free_heredoc_file_array(cmd);
}
