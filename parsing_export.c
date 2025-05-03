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
	if ((var[i] == '_') || (var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A' && var[i] <= 'Z'))
		i++;
	else
	{
		printf("btata\n");
		ft_putstr_fd("export: not an identifier: ", 1);
		ft_putstr_fd(var, 1);
		ft_putstr_fd("\n", 1);
		exit (1);
	}
	while (var[i])
	{
		printf("print --> %c ", var[i]);
		if (var[i] == '=')
			break ;
		if (is_notForbidden_char(var[i]) == 0 || var[i] == ' ')
		{
			printf("tafa7a\n");
			ft_putstr_fd("export: not an identifier: ", 1);
			ft_putstr_fd(var, 1);
			ft_putstr_fd("\n", 1);
			exit (1);
		}
		i++;
	}
	while (var[i])
	{
		printf("print --> %c ", var[i]);
		i++;
	}
	printf("\n");
	// if ( var[i] == '=')
	// {
	// 	printf("batbouta\n");
	// 	i++;
	// 	printf("var[i + 1] --> -%c-\n", var[i + 1]);
	// 	if (var[i] == ' ')
	// 	{
	// 		ft_putstr_fd("export: not an identifier: ", 1);
	// 		ft_putstr_fd(var, 1);
	// 		ft_putstr_fd("\n", 1);
	// 		exit (1);
	// 	}
	// }
	// else
	// 	return ;
}

// void    check_equal_sign(t_token **token, char *var)
// {
// 	char	*equal;
// 	int		len;

// 	equal = (*token)->value;
// 	len = ft_strlen(equal);
// 	if (len != 1 && equal[0] != '=')
// 	{
// 		ft_putstr_fd("export: not an identifier: ", 1);
// 		ft_putstr_fd(var, 1);
// 		ft_putstr_fd("\n", 1);
// 		exit (1);
// 	}
// }

void	ft_export(t_token **token)
{
	t_token	*token_tmp;
	// char	*var;

	if ((!token) || (ft_strncmp((*token)->value, "export", 6) != 0))
		return ;
	token_tmp = (*token);
	token_tmp = token_tmp->next;
	check_var(&token_tmp);
	// var = token_tmp->value;
	// token_tmp = token_tmp->next;
	// check_equal_sign(&token_tmp, var);
	// token_tmp = token_tmp->next->next;
}
