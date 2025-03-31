/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:15:35 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/31 14:44:24 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"

t_env	*create_env_node(char *type, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (false);
	node->type = ft_strdup(type);
	node->value = ft_strdup(value);
	node->next = NULL;
}

bool	set_env_value(t_env **env_list, char *type, char *value)
{
	t_env	*tmp;
	t_env	*new;

	if (!env_list || !type || !*type)
		return (false);
	tmp = *env_list;
	while (tmp)
	{
		if (ft_strcmp(tmp->type, type) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (true);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	new = create_env_node(type, value);
	if (!new)
		return (false);
	add_env_node(env_list, new);
	return (true);
}


void	env_delone(t_env *node)
{
	if (!node)
		return ;
	free(node->type);
	free(node->value);
	free(node);
}

void	unset_env(t_env **env, char *type)
{
	t_env	*delete_node;

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
