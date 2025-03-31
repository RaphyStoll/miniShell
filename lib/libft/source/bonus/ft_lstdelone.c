/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:29:26 by raphael           #+#    #+#             */
/*   Updated: 2025/03/31 12:07:32 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft_bonus.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		if (del != NULL)
		{
			del(lst->content);
		}
		free(lst);
	}
}
