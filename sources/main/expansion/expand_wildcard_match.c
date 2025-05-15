/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_match.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:01:43 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/01 12:12:48 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

void	handle_memory(int *i, int *j, int *star_idx, int *name_idx)
{
	*i = *star_idx + 1;
	*j = *name_idx + 1;
	*name_idx = *j;
}

void	handle_star(int *i, int *j, int *star_idx, int *name_idx)
{
	*star_idx = *i;
	*name_idx = *j;
	(*i)++;
}

bool	wildcard_match(char *arg, char *name)
{
	int	i;
	int	j;
	int	star_idx;
	int	name_idx;

	i = 0;
	j = 0;
	star_idx = -1;
	name_idx = -1;
	while (name[j])
	{
		if (arg[i] == name[j] && ++i && ++j)
			continue ;
		else if (arg[i] == '*')
			handle_star(&i, &j, &star_idx, &name_idx);
		else if (star_idx != -1)
			handle_memory(&i, &j, &star_idx, &name_idx);
		else
			return (false);
	}
	while (arg[i] == '*')
		i++;
	return (arg[i] == '\0');
}

void	sort_args_lexico(char **array, int count)
{
	bool	swap;
	int		i;
	char	*tmp;

	swap = true;
	while (swap)
	{
		swap = false;
		i = 0;
		while (i < count - 1)
		{
			if (ft_strcmp(array[i], array[i + 1]) > 0)
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				swap = true;
			}
			i++;
		}
	}
}
