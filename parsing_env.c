#include "minishell.h"

void	ft_env(t_token **token)
{
	t_token	*token_tmp;

	if ((!token) || (ft_strncmp((*token)->value, "env", 3) != 0))
		return ;
	token_tmp = (*token);
	token_tmp = token_tmp->next;
	if (token_tmp != NULL)
		return ;
}
