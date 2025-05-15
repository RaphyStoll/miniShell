/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_sort_replace.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:27:08 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/01 13:02:22 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

void	copy_new_args(char **matches, char **new_args, int *dst, int count)
{
	int	j;
	int	tmp;

	tmp = *dst;
	j = 0;
	while (j < count)
	{
		new_args[tmp] = matches[j];
		tmp++;
		j++;
	}
	*dst = tmp;
}

int	calculate_nb_args(t_node *node)
{
	int	nb_args;

	nb_args = 0;
	while (node->args[nb_args])
		nb_args++;
	return (nb_args);
}

char	**allocate_new_args(int nb_args, int count)
{
	char	**new_args;

	new_args = malloc(sizeof(char *) * (nb_args + count + 1));
	if (!new_args)
		return (perror("malloc new args failed"), NULL);
	return (new_args);
}

void	replace_args_in_list(t_node *node, int i, char **matches, int count)
{
	int		nb_args;
	char	**new_args;
	int		src;
	int		dst;

	nb_args = calculate_nb_args(node);
	if (nb_args < 0)
		return ;
	new_args = allocate_new_args(nb_args, count);
	src = 0;
	dst = 0;
	while (src < i)
		new_args[dst++] = node->args[src++];
	copy_new_args(matches, new_args, &dst, count);
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
