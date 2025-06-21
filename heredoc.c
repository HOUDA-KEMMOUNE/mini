/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:05:22 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/20 16:05:23 by hkemmoun         ###   ########.fr       */
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
				command_tmp->delimiter = token_tmp->value;
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
	// char		*path;
	static int	i;
	char		*num;
	(void)file_name;

	tmp = "/tmp/minishell_heredoc";
	num = ft_itoa(i);
	tmp = ft_strjoin(tmp, num);
	fd = open(tmp, O_CREAT | O_EXCL | O_RDONLY, 0600);
	if (fd < 0)
		perror("Failed to create a temp file");
	i++;
	return (fd);
}

void	heredoc(t_token **token, t_token_exc **command)
{
	t_token_exc	*command_tmp;
	t_token		*token_tmp;
	char		*line;
	char		*file_name;
	int			fd;

	if (!token || !(*token) || !command || !(*command))
		return ;
	line = NULL;
	command_tmp = (*command);
	token_tmp = (*token);
	if (check_heredoc(token, command) == 0)
	{
		return ;
	}
	fd = creat_tmpfile(&file_name); //TODO
	printf("re: %d\n", fd);
}
  