/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 19:21:40 by raphael           #+#    #+#             */
/*   Updated: 2025/02/20 14:12:17 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/libft.h"

static int	is_in_set(char c, const char *set)
{
	int	count;

	count = 0;
	while (set[count])
	{
		if (c == set[count])
			return (1);
		count++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*s2;
	int		count;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && is_in_set(s1[end], set))
		end--;
	if (start > end)
		return (ft_strdup(""));
	s2 = (char *)malloc(sizeof(char) * (end - start + 2));
	if (!s2)
		return (NULL);
	count = 0;
	while (start <= end)
		s2[count++] = s1[start++];
	s2[count] = '\0';
	return (s2);
}
