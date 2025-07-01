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

static void	handle_eof_warning(char *delimiter)
{
	if (isatty(STDIN_FILENO))
		ft_putstr_fd("minishell: warning: here-document \
delimited by end-of-file (wanted `", 2);
	else
		ft_putstr_fd("bash: warning: here-document at line 1 \
delimited by end-of-file (wanted `", 2);
	ft_putstr_fd(delimiter, 2);
	ft_putstr_fd("')\n", 2);
}

static void	trim_line_endings(char *line)
{
	int	len;

	if (line)
	{
		len = ft_strlen(line);
		while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r'))
		{
			line[len - 1] = '\0';
			len--;
		}
	}
}

void	fill_heredoc_file(int fd, char *delimiter)
{
	char	*line;
	t_env	*env_list;
	char	*prompt;

	env_list = *env_func();
	prompt = "> ";
	if (!isatty(STDIN_FILENO))
		prompt = "";
	while (1)
	{
		line = readline(prompt);
		if (!line)
		{
			handle_eof_warning(delimiter);
			return ;
		}
		trim_line_endings(line);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		process_heredoc_line(fd, line, env_list);
		free(line);
	}
}

void	create_heredoc_files(t_token_exc *command_tmp)
{
	int		i;
	int		fd;
	char	*file_name;

	i = 0;
	while (i < command_tmp->count_heredoc)
	{
		fd = creat_tmpfile(&file_name);
		command_tmp->heredoc_file[i] = ft_strdup(file_name);
		fill_heredoc_file(fd, command_tmp->delimiter[i]);
		if (fd >= 0)
			close(fd);
		free(file_name);
		i++;
	}
}

void	heredoc(t_token **token, t_token_exc **command)
{
	t_token_exc	*command_tmp;
	t_token		*token_tmp;

	if (!token || !(*token) || !command || !(*command))
		return ;
	command_tmp = (*command);
	token_tmp = (*token);
	command_tmp->count_heredoc = check_heredoc(token, command);
	if (command_tmp->count_heredoc == 0)
		return ;
	setup_heredoc_arrays(command_tmp);
	collect_delimiters(token_tmp, command_tmp);
	create_heredoc_files(command_tmp);
}
