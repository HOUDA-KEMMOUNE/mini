/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 15:33:19 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 15:33:37 by hkemmoun         ###   ########.fr       */
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
			if (token_tmp && (token_tmp->type == ARG
					|| token_tmp->type == CMD
					|| token_tmp->type == WORD
					|| token_tmp->type == DELIMITER))
			{
				token_tmp->type = DELIMITER;
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

void	process_heredoc_line(int fd, char *line, t_env *env_list)
{
	char	*expanded_line;

	if (ft_strchr(line, '$'))
	{
		expanded_line = expand_all_variables(line, env_list);
		ft_putstr_fd(expanded_line, fd);
		free(expanded_line);
	}
	else
		ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
}

void	setup_heredoc_arrays(t_token_exc *command_tmp)
{
	command_tmp->delimiter = malloc((command_tmp->count_heredoc + 1)
			* sizeof(char *));
	command_tmp->heredoc_file = malloc((command_tmp->count_heredoc + 1)
			* sizeof(char *));
	command_tmp->delimiter[command_tmp->count_heredoc] = NULL;
	command_tmp->heredoc_file[command_tmp->count_heredoc] = NULL;
}

void	collect_delimiters(t_token *token_tmp, t_token_exc *command_tmp)
{
	int	i;

	i = 0;
	while (token_tmp && i < command_tmp->count_heredoc)
	{
		if (token_tmp->type == HEREDOC)
		{
			token_tmp = token_tmp->next;
			if (token_tmp->type == DELIMITER || token_tmp->type == ARG
				|| token_tmp->type == CMD)
			{
				command_tmp->delimiter[i] = ft_strdup(token_tmp->value);
				i++;
			}
		}
		token_tmp = token_tmp->next;
	}
}
