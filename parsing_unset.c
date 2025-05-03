#include "minishell.h"

static void	after_dollar(char *var)
{
	int		i;

	i = 0;
	while (var[i])
	{
		if ((var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A' && var[i] <= 'Z')
		|| (var[i] >= '0' && var[i] <= '9'))
			i++;
		else if (var[i] == '(' || var[i] == ')')
		{
			if (var[i] == ')')
			{
				ft_putstr_fd("syntax error near unexpected token `)'\n", 1);
				exit (1);
			}
			else
			{
				ft_putstr_fd("syntax error near unexpected token `('\n", 1);
				exit (1);
			}
		}
		else
		{
			ft_putstr_fd("unset: `", 1);
			ft_putstr_fd(var, 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
			exit (1);
		}
	}
}

static void	check_var(t_token **token)
{
	char	*var;
	int		i;

	var = (*token)->value;
	i = 0;
	if ((var[i] == '_') || (var[i] >= 'a' && var[i] <= 'z')
	|| (var[i] >= 'A' && var[i] <= 'Z'))
		i++;
	else if (var[i] == '$')
	{
		after_dollar(&var[i]);
		i++;
	}
	else
	{
		ft_putstr_fd("unset: not an identifier: ", 1);
		ft_putstr_fd(var, 1);
		ft_putstr_fd("\n", 1);
		exit (1);
	}
	while (var[i])
	{
		if (var[i] == '=')
		{
			ft_putstr_fd("unset: `=': not a valid identifier\n", 1);
			exit (1);
		}
		else if (is_notForbidden_char(var[i]) == 0)
		{
			ft_putstr_fd("unset: not an identifier: ", 1);
			ft_putstr_fd(var, 1);
			ft_putstr_fd("\n", 1);
			exit (1);
		}
		i++;
	}
}

void	ft_unset(t_token **token)
{
	t_token	*token_tmp;

	if ((!token) || (ft_strncmp((*token)->value, "unset", 5) != 0))
		return ;
	token_tmp = (*token);
	token_tmp = token_tmp->next;
	while (token_tmp)
	{
		check_var(&token_tmp);
		token_tmp = token_tmp->next;
	}
	return ;
}
