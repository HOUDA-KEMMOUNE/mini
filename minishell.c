/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 19:32:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/20 12:02:46 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: %-10s | Type: %d\n", tokens->value, tokens->type);
		tokens = tokens->next;
	}
}

int main(void)
{
	char input[1024];
	t_token *tokens;

	while (1)
	{
		printf("minishell> ");
		if (!fgets(input, sizeof(input), stdin))
			break;

		// Remove trailing newline if any
		size_t len = strlen(input);
		if (len > 0 && input[len - 1] == '\n')
			input[len - 1] = '\0';

		tokens = lexer(input);
		if (tokens)
		{
			print_tokens(tokens);
			// Free token list here if needed
		}
	}
}