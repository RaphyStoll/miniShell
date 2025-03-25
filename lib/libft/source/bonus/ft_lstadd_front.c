/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 22:46:52 by raphael           #+#    #+#             */
/*   Updated: 2025/03/25 19:34:23 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft_bonus.h"

void	ft_lstadd_front(t_list **lst, t_list *l_new)
{
	if (lst && l_new)
	{
		if (l_new == NULL)
			return ;
		l_new->next = *lst;
		*lst = l_new;
	}
}
