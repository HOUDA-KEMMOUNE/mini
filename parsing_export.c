#include "minishell.h"

int	is_notForbidden_char(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || (c == '_'))
		return (1); // l2omore ta7t saytara ✅
	else
		return (0); // forbidden character ❌
}

static void    check_var(t_token **token)
{
	char	*var;
	int		i;

	var = (*token)->value;
	i = 0;
	if ((var[i] == '_') || (var[i] >= 'a' && var[i] <= 'z')
		|| (var[i] >= 'A' && var[i] <= 'Z'))
		i++;
	else
	{
		ft_putstr_fd("export: not an identifier: ", 1);
		ft_putstr_fd(var, 1);
		ft_putstr_fd("\n", 1);
		exit (1);
	}
	while (var[i])
	{
		if (var[i] == '=')
		{
			ft_putstr_fd("export: `=': not a valid identifier\n", 1);
			exit (1);
		}		
		else if (is_notForbidden_char(var[i]) == 0)
		{
			ft_putstr_fd("export: not an identifier: ", 1);
			ft_putstr_fd(var, 1);
			ft_putstr_fd("\n", 1);
			exit (1);
		}
		i++;
	}
}

void	ft_export(t_token **token)
{
	t_token	*token_tmp;
	// char	*var;

	if ((!token) || (ft_strncmp((*token)->value, "export", 6) != 0))
		return ;
	token_tmp = (*token);
	token_tmp = token_tmp->next;
	if (token_tmp->next == NULL)
		return ;
	while (token_tmp)
	{
		check_var(&token_tmp);
		token_tmp = token_tmp->next;
	}
	return ;
}
