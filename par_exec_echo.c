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

static void	redir_out_append(t_token **token, t_echo **echo_struct)
{
	t_token	*token_tmp;
	// int		i;
	
	if (!token || !(*token))
		return ;
	token_tmp = (*token);
	// i = 0;
	while (token_tmp)
	{
		if ((token_tmp->type == REDIR_OUT) || (token_tmp->type == APPEND))
		{
			//token_tmp = token_tmp->next;
			if (token_tmp->type == REDIR_OUT)
			{
				token_tmp = token_tmp->next;
				(*echo_struct)->fd = open(token_tmp->value, O_CREAT | O_WRONLY | O_TRUNC, 0640);
			}
			else if (token_tmp->type == APPEND)
			{
				token_tmp = token_tmp->next;
				(*echo_struct)->fd = open(token_tmp->value, O_CREAT | O_RDWR | O_APPEND, 0640);
			}
			if ((*echo_struct)->fd <= 0)
			{
				ft_putstr_fd("Sorry, We can't open this file :(\n", 1);
				exit (1);
			}
		}
		token_tmp = token_tmp->next;
	}
}

void	echo(t_token **token, t_echo **echo_struct)
{
	t_echo	*echo_struct_tmp;
	t_token	*token_tmp;
	t_token	*head;
	char	*s;
	//int		red;

	if ((!token) || (ft_strncmp((*token)->value, "echo", 4) != 0))
		return ;
	token_tmp = (*token);
	head = (*token)->next;
	echo_struct_tmp = (*echo_struct);
	redir_out_append(token, &echo_struct_tmp);
	if (token_tmp->type == WORD)
	{
		if (ft_strncmp(token_tmp->value, "echo", 4) == 0)
		{
			if (token_tmp->next == NULL)
			{
				ft_putstr_fd("\n", echo_struct_tmp->fd);
				return ;
			}
			token_tmp = token_tmp->next;
			if (token_tmp->type != WORD)
				print_echo_error();
			else if (ft_strncmp(token_tmp->value, "-n", 2) == 0)
			{
				if (token_tmp->next == NULL)
					return ;
				token_tmp = token_tmp->next;
			}
			if ((token_tmp->type == WORD) || (token_tmp->type == REDIR_OUT) || (token_tmp->type == APPEND))
			{
				while (token_tmp)
				{
					s = token_tmp->value;
					while (*s)
					{
						if ((ft_strncmp(s, ">", 1) == 0) || (ft_strncmp(s, ">>", 2) == 0))
							break ;
						write(echo_struct_tmp->fd, s, 1);
						s++;
					}
					if ((token_tmp->next != NULL))
						write(echo_struct_tmp->fd, " ", 1);
					if ((ft_strncmp(token_tmp->value, ">", 1) == 0)
						|| (ft_strncmp(token_tmp->value, ">>", 2) == 0))
						token_tmp = token_tmp->next->next;
					else
					token_tmp = token_tmp->next;
				}
				if (ft_strncmp(head->value, "-n", 2) != 0)
					write(echo_struct_tmp->fd, "\n", 1);
			}
			else
				return ;
				// print_error_command(&token_tmp);
		}
	}
	// free (echo_struct);
}

// void	ft_echo(t_token **token, t_echo **echo_struct)
// {
// 	t_echo	*echo_struct_tmp;
// 	t_token	*token_tmp;
// 	char	*s;
// 	//int		red;

// 	if ((!token) || (ft_strncmp((*token)->value, "echo", 4) != 0))
// 		return ;
// 	token_tmp = (*token);
// 	echo_struct_tmp = (*echo_struct);
// 	redir_out_count(token, &echo_struct_tmp);
// 	if (token_tmp->type == WORD)
// 	{
// 		if (ft_strncmp(token_tmp->value, "echo", 4) == 0)
// 		{
// 			token_tmp = token_tmp->next;
// 			if (token_tmp->type != WORD)
// 				print_echo_error();
// 			else if (ft_strncmp(token_tmp->value, "-n", 2) == 0)
// 				ft_echo_helper(&token_tmp, &echo_struct_tmp);
// 			else if ((token_tmp->type == WORD) || (token_tmp->type == REDIR_OUT))
// 			{
// 				while (token_tmp)
// 				{
// 					s = token_tmp->value;
// 					while (*s)
// 					{
// 						if (ft_strncmp(s, ">", 1) == 0)
// 							break ;
// 						write(echo_struct_tmp->fd, s, 1);
// 						s++;
// 					}
// 					if ((token_tmp->next != NULL))
// 						write(echo_struct_tmp->fd, " ", 1);
// 					if (ft_strncmp(token_tmp->value, ">", 1) == 0)
// 						token_tmp = token_tmp->next->next;
// 					else
// 					token_tmp = token_tmp->next;
// 				}
// 				write(echo_struct_tmp->fd, "\n", 1);
// 			}
// 			else
// 				print_error_command(&token_tmp);
// 		}
// 	}
// }
