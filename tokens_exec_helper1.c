/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_exec_helper1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 09:07:55 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/25 14:04:48 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokens_exc_helper1(t_token_exc **new, t_token **token)
{
	(*new)->cmd = (*token)->value;
	(*new)->fd_in = STDIN_FILENO;
	(*new)->fd_out = STDOUT_FILENO;
	(*new)->next = NULL;
}

void	tokens_exc_helper2(t_token_exc **new, t_token_exc **token_list)
{
	t_token_exc	*temp;

	if ((*token_list) == NULL)
		(*token_list) = (*new);
	else
	{
		temp = (*token_list);
		while (temp->next)
			temp = temp->next;
		temp->next = (*new);
	}
}

int	open_file_by_type(char *filename, int type)
{
	int	fd;

	if (type == REDIR_OUT)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (type == REDIR_IN)
		fd = open(filename, O_RDONLY);
	else
		return (-1);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(filename);
		return (-1);
	}
	return (fd);
}

void	assign_fd_to_token(t_token_exc **token_list, int fd, int type)
{
	if (type == REDIR_OUT || type == APPEND)
	{
		if ((*token_list)->fd_out != STDOUT_FILENO)
			close((*token_list)->fd_out);
		(*token_list)->fd_out = fd;
	}
	else if (type == REDIR_IN)
	{
		if ((*token_list)->fd_in != STDIN_FILENO)
			close((*token_list)->fd_in);
		(*token_list)->fd_in = fd;
	}
}

int	handle_redir(t_token *token_tmp, t_token_exc **token_list, int type)
{
	int	fd;

	if (!token_tmp || !token_tmp->next || !token_list || !(*token_list))
		return (-1);
	token_tmp = token_tmp->next;
	if ((*token_list)->file)
		free((*token_list)->file);
	(*token_list)->file = ft_strdup(token_tmp->value);
	if (!(*token_list)->file)
		return (-1);
	fd = open_file_by_type(token_tmp->value, type);
	if (fd < 0)
		return (-1);
	assign_fd_to_token(token_list, fd, type);
	return (0);
}
