/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:05:22 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/22 14:33:43 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_token **token, t_token_exc **command)
{
	t_token		*token_tmp;
	t_token_exc	*command_tmp;
	int			check;

	check = 0;
	token_tmp = (*token);
	command_tmp = (*command);
	while (token_tmp)
	{
		if (token_tmp->type == HEREDOC)
		{
			token_tmp = token_tmp->next;
			if (token_tmp->type == ARG
				|| token_tmp->type == CMD)
			{
				token_tmp->type = DELIMITER;
				command_tmp->delimiter = ft_strdup(token_tmp->value);
				check++;
			}
		}
		token_tmp = token_tmp->next;
	}
	(*command) = command_tmp;
	return (check);
}

int	creat_tmpfile(char **file_name)
{
	int			fd;
	char		*tmp;
	char		*tmp_file;
	char		*num;
	static int	i;

	tmp = "/tmp/minishell_heredoc";
	num = ft_itoa(i);
	tmp_file = ft_strjoin(tmp, num);
	free(num);
	fd = open(tmp_file, O_CREAT | O_EXCL | O_RDWR, 0600);
	while (fd < 0)
	{
		free(tmp_file);
		i++;
		num = ft_itoa(i);
		tmp_file = ft_strjoin(tmp, num);
		free(num);
		fd = open(tmp_file, O_CREAT | O_EXCL | O_RDWR, 0600);
	}
	i++;
	(*file_name) = tmp_file;
	return (fd);
}

void	fill_heredoc_file(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return ;
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
}

void	heredoc(t_token **token, t_token_exc **command)
{
	t_token_exc	*command_tmp;
	t_token		*token_tmp;
	char		*file_name;
	int			fd;

	if (!token || !(*token) || !command || !(*command))
		return ;
	command_tmp = (*command);
	token_tmp = (*token);
	if (check_heredoc(token, command) == 0)
		return ;
	fd = creat_tmpfile(&file_name);
	fill_heredoc_file(fd, command_tmp->delimiter); //TODO
	if (fd >= 0)
	{
		unlink(file_name);
		close(fd);
	}
	free (file_name);
}
