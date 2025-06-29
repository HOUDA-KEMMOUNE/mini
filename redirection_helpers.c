/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:00:00 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/29 10:00:00 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_file(int *fd, t_token **redir_token, t_token **token_tmp)
{
	if ((*redir_token)->type == REDIR_OUT)
		*fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_TRUNC, 0640);
	else
		*fd = open((*token_tmp)->value, O_CREAT | O_WRONLY | O_APPEND, 0640);
}
