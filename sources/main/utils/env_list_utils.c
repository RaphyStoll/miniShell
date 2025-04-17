/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:14:38 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/16 23:19:38 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "../../../lib/libft/header/libft.h"
#include "error_code.h"
#include "utils.h"

static void	one_more_line(t_env **copy, t_env **last)
{
	*copy = NULL;
	*last = NULL;
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

	one_more_line(&copy, &last);
	while (src)
	{
		new_node = ft_calloc(1, sizeof(t_env));
		if (!new_node)
			return (NULL);
		new_node->type = ft_strdup(src->type);
		if (!new_node->type)
			return (free_env(new_node), NULL);
		new_node->value = ft_strdup(src->value);
		if (!new_node->value)
			return (free_env(new_node), NULL);
		new_node->next = NULL;
		if (!copy)
			copy = new_node;
		else
			last->next = new_node;
		last = new_node;
		src = src->next;
	}
	return (copy);
}

t_env	*sorted_merge(t_env *a, t_env *b)
{
	t_env	*result;

	result = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (ft_strcmp(a->type, b->type) <= 0)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return (result);
}

void	split_list(t_env *source, t_env **front, t_env **back)
{
	t_env	*slow;
	t_env	*fast;

	slow = source;
	fast = source->next;
	while (fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

/*
	Si la liste est vide ou contient un seul élément → rien à faire
	•	Sinon :
	•	Elle la coupe en deux
	•	Elle trie récursivement chaque moitié
	•	Elle les fusionne et remet le résultat dans *head_ref
*/

void	sort_env(t_env **head_ref)
{
	t_env	*head;
	t_env	*a;
	t_env	*b;

	head = *head_ref;
	if (!head || head->next == NULL)
		return ;
	split_list(head, &a, &b);
	sort_env(&a);
	sort_env(&b);
	*head_ref = sorted_merge(a, b);
}
