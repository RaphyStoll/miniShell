/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:01:43 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/28 15:34:12 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "debbug.h"

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

void	replace_args_in_list(t_node *node, int i, char **matches, int count)
{
	int		nb_args;
	char	**new_args;
	int		src;
	int		dst;
	int		j;

	nb_args = 0;
	while (node->args[nb_args])
		nb_args++;
	new_args = malloc(sizeof(char *) * (nb_args + count));
	if (!new_args)
	{
		perror("malloc new args failed");
		return ;
	}
	src = 0;
	dst = 0;
	while (src < i)
		new_args[dst++] = node->args[src++];
	j = 0;
	while (j < count)
		new_args[dst++] = matches[j++];
	src = i + 1;
	while (src < nb_args)
	{
		new_args[src] = node->args[src];
		i++;
	}
	new_args[dst] = NULL;
	free(node->args);
	node->args = new_args;
}
