/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:21:04 by raphael           #+#    #+#             */
/*   Updated: 2025/03/25 19:34:42 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft_bonus.h"

void	ft_lstadd_back(t_list **lst, t_list *l_new)
{
	t_list	*current;

	if (l_new == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = l_new;
		return ;
	}
	current = *lst;
	while (current->next != NULL)
		current = current->next;
	current->next = l_new;
}
