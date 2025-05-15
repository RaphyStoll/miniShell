/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:14:38 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/01 12:13:02 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "env_struct.h"
#include "error_code.h"
#include "utils.h"

static t_env	*copy_env_node(t_env *src)
{
	t_env	*new_node;

	new_node = ft_calloc(1, sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->type = ft_strdup(src->type);
	if (!new_node->type)
		return (free_env(new_node), NULL);
	if (src->value)
	{
		new_node->value = ft_strdup(src->value);
		if (!new_node->value)
			return (free_env(new_node), NULL);
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Permet de doubliquer la liste chainer t_env
 * 
 * @param src represente la liste source
 * @return * t_env* 
 */
t_env	*env_dup(t_env *src)
{
	t_env	*copy;
	t_env	*last;
	t_env	*new_node;

	copy = NULL;
	last = NULL;
	while (src)
	{
		new_node = copy_env_node(src);
		if (!new_node)
			return (free_env(copy), NULL);
		if (!copy)
			copy = new_node;
		else
			last->next = new_node;
		last = new_node;
		src = src->next;
	}
	return (copy);
}
