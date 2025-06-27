/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 22:03:42 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/24 12:58:02 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	validate_with_equals(t_token *current)
{
	char	*eq;
	char	*key_backup;

	eq = ft_strchr(current->value, '=');
	*eq = '\0';
	key_backup = ft_strdup(current->value);
	*eq = '=';
	if (!is_valid_identifier(key_backup))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(current->value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(key_backup);
		return (1);
	}
	free(key_backup);
	return (0);
}

static int	validate_single_arg(t_token *current)
{
	char	*eq;

	eq = ft_strchr(current->value, '=');
	if (eq)
		return (validate_with_equals(current));
	else if (!is_valid_identifier(current->value))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(current->value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

static int	validate_export_args(t_token *current)
{
	int	error_occurred;

	error_occurred = 0;
	while (current)
	{
		if (validate_single_arg(current))
			error_occurred = 1;
		current = current->next;
	}
	return (error_occurred);
}

int	export_internal(t_token *tokens, t_env **env_list)
{
	t_token	*current;

	current = tokens->next;
	if (!current)
	{
		export_print_sorted(*env_list);
		return (0);
	}
	if (validate_export_args(current))
		return (1);
	execute_export_args(current, env_list);
	return (0);
}

// t_env	*export(t_token *tokens, t_env *env_list)
// {
// 	export_internal(tokens, &env_list);
// 	return (env_list);
// }

// int	export_wrapper(t_token *tokens, t_env **env_list)
// {
// 	t_env *new_head = export(tokens, *env_list); // pass current head
// 	if (new_head != *env_list)
// 		*env_list = new_head; // update the caller's pointer
// 	return (0);
// }

int	export_builtin_adapter(t_token *tokens, t_env **env_list)
{
	export_internal(tokens, env_list);
	return (0);
}
