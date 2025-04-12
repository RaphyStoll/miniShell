/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:15:35 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/12 16:41:54 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "minishell.h"

/**
 * @brief Allocates and initializes a new t_env node.
 * 
 * @param type Type of the environment variable.
 * @param value Value associated with the variable.
 * @return Pointer to the new node, or NULL on allocation failure.
 */
t_env	*create_env_node(char *type, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (false);
	node->type = ft_strdup(type);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

/**
 * @brief Sets or updates a variable in the environment list.
 * 
 * @param env_list Address of the pointer to the environment list.
 * @param type Type of variable to set or update.
 * @param value New value to assign to the variable.
 * @return true if successful, false on failure to handle error.
 */
bool	set_env_value(t_env **env_list, char *type, char *value)
{
	t_env	*tmp;
	t_env	*new;
	char	*new_value;

	if (!env_list || !type || !*type)
		return (false);
	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, type) == 0)
		{
			new_value = ft_strdup(value);
			if (!new_value)
				return (false);
			free(tmp->value);
			tmp->value = new_value;
			return (true);
		}
		tmp = tmp->next;
	}
	new = create_env_node(type, value);
	if (!new)
		return (false);
	add_env_node(env_list, new);
	return (true);
}

/**
 * @brief Frees a single t_env node, including its type and value.
 * 
 * @param to_delete Node to free.
 */
void	env_delone(t_env *node)
{
	if (!node)
		return ;
	if (!node->type)
		free(node->type);
	if (!node->value)
		free(node->value);
	if (!node)	
		free(node);
}

/**
 * @brief Removes a variable from the environment list.
 * 
 * @param env Address of the pointer to the environment list.
 * @param type Name of the variable to remove.
 */
void	unset_env(t_env **env, char *type)
{
	t_env	*delete_node;

	if (!env || !*env)
		return ;
	while (env && *env)
	{
		if (strcmp((*env)->type, type) == 0)
		{
			delete_node = *env;
			*env = (*env)->next;
			env_delone(delete_node);
			return ;
		}
		env = &(*env)->next;
	}
}
