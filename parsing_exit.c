#include "minishell.h"

static int	ft_isalpha(char *str)
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
	token_tmp = token_tmp->next;
	str = token_tmp->value;
	if (ft_isalpha(str) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit (255);
	}
	num = (int)token_tmp->value;
	if (num >= 0 && num <= 255)
		return (num);
	else
		return (num % 256);
	token_tmp = token_tmp->next;
	if (token_tmp != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return ;
	}
}
