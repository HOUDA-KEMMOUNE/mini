/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_exec_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:03:38 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:03:44 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_out_count(t_token **token, t_echo	**echo_struct)
{
	t_token	*token_tmp;
	// int		i;
	
	printf("lbatbouut\n");
	if (!token || !(*token))
		return ;
	token_tmp = (*token);
	// i = 0;
	while (token_tmp)
	{
		if (token_tmp->type == REDIR_OUT)
		{
			token_tmp = token_tmp->next;
			(*echo_struct)->fd = open(token_tmp->value, O_RDWR);
			printf("fd --> %d\n", (*echo_struct)->fd);
		}
		// else if (token_tmp->type == WORD)
		// 	i++;
		token_tmp = token_tmp->next;
	}
}

static void	ft_echo_helper(t_token **token_tmp, t_echo **echo_struct)
{
	char	*s;
	
	(*token_tmp) = (*token_tmp)->next;
	while ((*token_tmp) != NULL)
	{
		if (((*token_tmp)->type == WORD) || ((*token_tmp)->type == REDIR_OUT))
		{
			if ((*token_tmp)->type == REDIR_OUT)
				(*token_tmp) = (*token_tmp)->next->next;
			else
			{
				s = (*token_tmp)->value;
				while (*s)
				{
					write((*echo_struct)->fd, s, 1);
					s++;
				}
				if ((*token_tmp)->next != NULL)
					write((*echo_struct)->fd, " ", 1);
			}
		}
		else
			print_error_command(token_tmp);
		(*token_tmp) = (*token_tmp)->next;
	}
}

void	ft_echo(t_token **token, t_echo **echo_struct)
{
	t_echo	*echo_struct_tmp;
	t_token	*token_tmp;
	char	*s;

	if ((!token) || (ft_strncmp((*token)->value, "echo", 4) != 0))
		return ;
	token_tmp = (*token);
	echo_struct_tmp = (*echo_struct);
	printf("msamn\n");
	redir_out_count(token, &echo_struct_tmp);
	printf("jaj 7amar\n");
	if (token_tmp->type == WORD)
	{
		if (ft_strncmp(token_tmp->value, "echo", 4) == 0)
		{
			token_tmp = token_tmp->next;
			if (token_tmp->type != WORD)
				print_echo_error();
			else if (ft_strncmp(token_tmp->value, "-n", 2) == 0)
				ft_echo_helper(&token_tmp, &echo_struct_tmp);
			else if ((token_tmp->type == WORD) || (token_tmp->type == REDIR_OUT))
			{
				if (token_tmp->type == REDIR_OUT)
					token_tmp = token_tmp->next->next;
				else
				{
					while (token_tmp)
					{
						s = token_tmp->value;
						while (*s)
						{
							write(echo_struct_tmp->fd, s, 1);
							s++;
						}
						if ((token_tmp->next != NULL))
							write(echo_struct_tmp->fd, " ", 1);
						token_tmp = token_tmp->next;
					}
					write(echo_struct_tmp->fd, "\n", 1);
				}
			}
			else
				print_error_command(&token_tmp);
		}
	}
}
