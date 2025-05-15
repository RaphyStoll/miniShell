/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:07:45 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/01 12:34:50 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "minishell.h"
#include "utils.h"

/**
 * @brief Get the value of a variable from the environment list.
 * 
 * @param env Environment list.
 * @param type Type of variable to search.
 * @return The value associated with the variable, or NULL if not found.
 */
char	*get_env_value(t_shell *shell, char	*type)
{
	t_env	*env;
	char	*value;

	if (!shell || !type)
		return (NULL);
	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->type, type) == 0)
		{
			value = ft_strdup(env->value);
			if (!value)
				return (free_env(env), NULL);
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}

t_env	*get_last_node(t_env *dup_env)
{
	if (!dup_env)
		return (NULL);
	while (dup_env->next)
		dup_env = dup_env->next;
	return (dup_env);
}

void	append_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (*env == NULL)
		*env = new_node;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
