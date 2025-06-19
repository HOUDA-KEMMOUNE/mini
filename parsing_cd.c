/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:04:13 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/05/31 17:44:56 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_cd(t_token **token, t_env *env_list)
// {
// 	t_token	*token_tmp;
// 	char	*expanded_path;
// 	int		arg_count;
// 	t_token	*arg_ptr;

// 	arg_count = 0;
// 	if ((!token) || (ft_strcmp((*token)->value, "cd") != 0))
// 		return ;

// 	token_tmp = (*token);
// 	if (token_tmp->next == NULL)
// 		return ;
// 	arg_ptr = token_tmp->next;
// 	while (arg_ptr && arg_ptr->type == WORD)
// 	{
// 		arg_count++;
// 		arg_ptr = arg_ptr->next;
// 	}
// 	token_tmp = token_tmp->next;

// 	if (arg_count > 1)
// 	{
// 		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
// 		return ;
// 	}

// 	if (check_commande(token_tmp->value) == 0)
// 	{
// 		ft_putstr_fd("minishell: cd: ", 1);
// 		ft_putstr_fd(token_tmp->value, 1);
// 		ft_putstr_fd(": No such file or directory\n", 1);
// 		return ;
// 	}

// 	if (check_commande(token_tmp->value) == 4)
// 	{
// 		ft_putstr_fd("cd: cannot access '", 1);

// 		// Expand variable in token_tmp->value
// 		expanded_path = expand_variable(token_tmp->value, env_list);
// 		ft_putstr_fd(expanded_path, 1);
// 		free(expanded_path);

// 		ft_putstr_fd("': No such file or directory\n", 1);
// 	}

// 	ft_count_dotes(token);
// }

void	ft_cd(t_token **token, t_env *env_list)
{
	t_token	*token_tmp;
	int		arg_count;
	t_token	*arg_ptr;

	arg_count = 0;
	(void)env_list;
	if ((!token) || (ft_strcmp((*token)->value, "cd") != 0))
		return ;
	token_tmp = (*token);
	if (token_tmp->next == NULL)
		return ;
	// Count args
	arg_ptr = token_tmp->next;
	while (arg_ptr && arg_ptr->type == WORD)
	{
		arg_count++;
		arg_ptr = arg_ptr->next;
	}
	if (arg_count > 1)
		return ; // Just return, error handled elsewhere
	token_tmp = token_tmp->next;
	// Basic check_command calls but no error printing here
	if (check_commande(token_tmp->value) == 0)
		return ; // No such file or directory error handled elsewhere
	if (check_commande(token_tmp->value) == 4)
		return ; // No such file or directory error handled elsewhere
	ft_count_dotes(token);
}
