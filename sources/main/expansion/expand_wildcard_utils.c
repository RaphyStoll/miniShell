/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 18:01:43 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/27 19:37:44 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "debbug.h"

bool	wildcard_match(char *arg, char *name)
{
	
}

void	sort_arg_lexico(char **array, int count)
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
			if (ft_strcmp(array[i], array[i + 1] > 0))
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

void	replace_args_in_list(t_node *node, int i, char *matches, int count)
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
		return (NULL);
	src = 0;
	dst = 0;
	while (src < i)
		new_args[dst++] = node->args[src++];
	j = 0;
	while (j < count)
		new_args[dst++] = matches[j++];
	src = i + 1;
	while (src < nb_args)
		new_args[src++] = node->args[src++];
	new_args[dst] = NULL;
	free(node->args);
	node->args = new_args;
}
