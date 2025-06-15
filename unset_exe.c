/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 11:05:09 by akemmoun          #+#    #+#             */
/*   Updated: 2025/06/15 15:39:39 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void unset_env_var(t_env **env, const char *name)
{
    t_env *curr = *env;
    t_env *prev = NULL;

    while (curr) {
        if (strcmp(curr->key, name) == 0) {
            if (prev)
                prev->next = curr->next;
            else
                *env = curr->next;
            free(curr->key);
            free(curr->value);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

int unset(t_token *tokens, t_env **env_list)
{
    t_token *arg = tokens->next; // skip "unset" itself

    while (arg)
    {
        char *name = arg->value;

        // Validate identifier
        if (!is_notForbidden_char(name[0], 1)) {
            fprintf(stderr, "unset: `%s': not a valid identifier\n", name);
            arg = arg->next;
            continue;
        }
        int valid = 1;
        for (int j = 1; name[j]; j++) {
            if (!is_notForbidden_char(name[j], 0)) {
                fprintf(stderr, "unset: `%s': not a valid identifier\n", name);
                valid = 0;
                break;
            }
        }
        if (valid)
            unset_env_var(env_list, name);

        arg = arg->next;
    }
    return 0;
}
