
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:31:56 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/14 14:32:51 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*dup;
	int		i;

	i = 0;
	dup = malloc(len + 1);
	if (!dup)
	{
		return (NULL);
	}
	while (i < len)
	{
		dup[i] = s1[i];
		i++;
	}
	dup[len] = '\0';
	return (dup);
}