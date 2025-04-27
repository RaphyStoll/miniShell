/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:40:39 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/27 17:06:46 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "debbug.h"



char	**collect_matches(char *arg, int count)
{
}

int	count_matches(char *arg)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;
	char			*name;

	dir = opendir(".");
	if (!dir)
		return (-1);
	count = 0;
}

bool	expand_single_wildcard_arg(t_node *node, int *index, t_shell *shell)
{
	int		count;
	int		i;
	char	*matches;

	i = *index;
	count = count_matches(node->args[i]);
	if (count < 0)
		return (false);
	if (count == 0)
	{
		*index = i + 1;
		return (true);
	}
	matches = collect_matches(node->args[i], count);
	if (!matches)
		return (false);
	sort_args_lexico(matches, count);
	replace_args_in_list(node, i, matches, count);
	*index = i + count;
	return (true);
}

bool	contains_wildcard(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '*')
			return (true);
		else
			i++;
	}
	return (false);
}
