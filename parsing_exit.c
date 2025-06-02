/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:12:03 by akemmoun          #+#    #+#             */
/*   Updated: 2025/05/14 13:12:07 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isalpha_exit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z'))
			return (0); // l2omoor ba2at bil fachal ❌
		else
			i++;
	}
	return (1); // l2omore madbota ✅
}

void	ft_exit(t_token **token)
{
	t_token	*token_tmp;
	int		num;
	char	*str;

	token_tmp = (*token);
	if ((!token) || (ft_strncmp((*token)->value, "exit", 4) != 0))
		return ;
	if (token_tmp->next == NULL)
		exit (0);
	token_tmp = token_tmp->next;
	str = token_tmp->value;
	if (ft_isalpha_exit(str) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit (2);
	}
	else if (token_tmp->next != NULL)
	{
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 1);
		return ;
	}
	num = ft_atoi(str);
	exit (num);
}
