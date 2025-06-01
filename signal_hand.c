/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_hand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkemmoun <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:48:14 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/18 15:48:15 by hkemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handler_sigint(int sig_num)
{
	(void)sig_num;
	// ft_putstr_fd("^C\n", 1);
	ft_putstr_fd("minishell> ^C\n", 1);
	ft_putstr_fd("minishell> ", 1);
	return ;
}

void	disable_sig(void)
{
	struct termios	term_echo_hand;

	if (tcgetattr(STDIN_FILENO, &term_echo_hand) == -1)
	{
		printf("tcgetattr\n");
		exit (0);
	}
	term_echo_hand.c_lflag &= ~(ECHOCTL);	
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term_echo_hand) == -1)
	{
		printf("tcsetattr\n");
		exit (0);
	}
}

