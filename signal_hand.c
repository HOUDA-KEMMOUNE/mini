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
    printf("^C\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	// printf("minishell> ");// signal(SIGINT, handler_sigint);
	// printf("^C\n");
}

void	handler_sigint_child(int sig_num)
{
	(void)sig_num;
    // printf("\n^C");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	printf("^C\n");
	printf("minishell> ");
	exit (0);
}

void	sig_quit_handler(int sig_num)
{
	(void)sig_num;
    printf("\n^C");
    // rl_on_new_line();
    // rl_replace_line("", 0);
    // rl_redisplay();
	printf("^\'Quit (core dumped)\n");
	// printf("minishell> ");
	exit (0);
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

