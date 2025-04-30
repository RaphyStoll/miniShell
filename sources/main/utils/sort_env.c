/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 22:43:46 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/30 17:17:42 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "env_struct.h"
#include "error_code.h"
#include "utils.h"
#include "debbug.h"

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
