/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:34:35 by akemmoun          #+#    #+#             */
/*   Updated: 2025/04/25 10:02:26 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **prepare_argv(t_token *token_list)
// {
// 	t_token *curr;
// 	int argc;
// 	char **argv;
// 	int i;

// 	curr = token_list;
// 	argc = 0;
// 	while (curr)
// 	{
// 		if (curr->type == WORD)
// 			argc++;
// 		curr = curr->next;
// 	}
// 	argv = malloc((argc + 1) * sizeof(char* ));
// 	if (!argv)
// 		return (NULL);
// 	curr = token_list;
// 	i = 0;
// 	while (curr)
// 	{
// 		if ()
// 	}
// }