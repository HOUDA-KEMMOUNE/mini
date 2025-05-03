/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_ls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:08:45 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/04/24 10:08:46 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count(char *s, int *count)
{
	while (*s)
	{
		if (*s == '.')
            *count = *count + 1;
		else
			return ;
		s++;
	}
}

static void	ft_count_dotes(t_token **token)
{
	t_token *token_tmp;
	char	*s;
	int		count;

	if ((!token))
		return ;
	count = 0;
	token_tmp = (*token);
	token_tmp = token_tmp->next;
	if (token_tmp->type == WORD)
	{
		s = token_tmp->value;
		ft_count(s, &count);
	}
	else
		return ;
	if (count > 2)
	{
		ft_putstr_fd("ls: ", 1);
		ft_putstr_fd(s, 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		exit (1);
	}
}

int	check_commande(char *input)
{
	if (ft_strncmp(input, "ls", 2) == 0)
		return (0);
	else if (ft_strncmp(input, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(input, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(input, "export", 6) == 0)
		return (0);
	else if (ft_strncmp(input, "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(input, "env", 3) == 0)
		return (0);
	else if (ft_strncmp(input, "exit", 4) == 0)
		return (0);
	else
		return (1);
}

void	ft_ls(t_token **token)
{
	t_token	*token_tmp;

	if ((!token) || (ft_strncmp((*token)->value, "ls", 2) != 0))
		return ;
	token_tmp = (*token);
	if (token_tmp->next == NULL)
		exit (0);
	token_tmp = token_tmp->next;
	if (check_commande(token_tmp->value) == 0)
	{
		ft_putstr_fd("ls: cannot access '", 1);
		ft_putstr_fd(token_tmp->value, 1);
		ft_putstr_fd("': No such file or directory\n", 1);
		exit(1);
	}
	ft_count_dotes(token);
}
