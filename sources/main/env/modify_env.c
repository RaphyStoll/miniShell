/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:15:35 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/31 12:13:26 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"

bool	set_env_value(t_env **env, char *type, char *value)
{
	
}


void	env_delone(t_env *node)
{
	if (!node)
		return ;
	free(node->type);
	free(node->value);
	free(node);
}

bool	unset_env(t_env **env, char *type)
{
	t_env	*delete_node;

	while (env)
	{
		if (strcmp((*env)->type, type) == 0)
		{
			delete_node = *env;
			env = (*env)->next;
			env_delone(delete_node);
			return (true);
		}
		env = &(*env)->next;
	}
	return (false);
}
