#include "minishell.h"

static int	ft_isalpha_exit(char *str)
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
	if (token_tmp->next == NULL)
		exit (0);
	token_tmp = token_tmp->next;
	str = token_tmp->value;
	if (ft_isalpha_exit(str) == 0)
	{
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(str, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit (255);
	}
	else if (token_tmp->next != NULL)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		return ;
	}
	num = ft_atoi(str);
	if (num >= 0 && num <= 255)
		exit (num);
	else if (num < 0 || num > 255)
		exit (num % 256);
}
