/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 16:40:39 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/01 12:12:53 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

int	fill_matches(DIR *dir, char **matches, int *ptr_j, char *arg)
{
	struct dirent	*entry;
	int				j;
	char			*name;

	j = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		name = entry->d_name;
		if ((name[0] != '.' || arg[0] == '.') && wildcard_match(arg, name))
		{
			matches[j] = ft_strdup(name);
			if (!matches[j])
			{
				*ptr_j = j;
				return (false);
			}
			j++;
		}
		entry = readdir(dir);
	}
	*ptr_j = j;
	return (true);
}

char	**collect_matches(char *arg, int count)
{
	DIR				*dir;
	int				j;
	char			**matches;

	matches = malloc(sizeof(char *) * (count + 1));
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (free(matches), NULL);
	if (!fill_matches(dir, matches, &j, arg))
	{
		while (j > 0)
		{
			j--;
			free(matches[j]);
		}
		closedir(dir);
		return (free(matches), NULL);
	}
	closedir(dir);
	matches[j] = NULL;
	return (matches);
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
	entry = readdir(dir);
	while (entry)
	{
		name = entry->d_name;
		if ((name[0] != '.' || arg[0] == '.') && wildcard_match(arg, name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

bool	expand_single_wildcard_arg(t_node *node, int *index)
{
	int		count;
	int		i;
	char	**matches;

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
