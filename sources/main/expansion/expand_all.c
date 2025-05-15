/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:40:45 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/05 16:13:53 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

/**
 * @brief Remove empty, unquoted arguments from a node.
 *
 * Compacts node->args and node->arg_quotes by discarding entries
 * where QUOTE_NONE and args[i] is "".
 *
 * @param node AST node with args and arg_quotes arrays.
 * @return true on success or no-op; false if inputs are NULL.
 */
bool	remove_empty_args(t_node *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!node || !node->args || !node->arg_quotes)
		return (true);
	while (node->args[i])
	{
		if (!(node->arg_quotes[i] == QUOTE_NONE && node->args[i][0] == '\0'))
		{
			node->args[j] = node->args[i];
			node->arg_quotes[j] = node->arg_quotes[i];
			j++;
		}
		i++;
	}
	node->args[j] = NULL;
	node->arg_quotes[j] = 0;
	return (true);
}

bool	expand_wildcard(t_node *node)
{
	int		i;

	i = 0;
	while (node->args[i])
	{
		if (contains_wildcard(node->args[i]))
		{
			if (!expand_single_wildcard_arg(node, &i))
				return (false);
		}
		else
			i++;
	}
	return (true);
}

/**
 * @brief Expands variables in redirection targets.
 *
 * Replaces variables like $VAR or $? in redirection targets,
 * except when the target is surrounded by single quotes.
 *
 * @param node The AST command node containing redirections.
 * @param shell The shell context.
 * @return true on success, false on error.
 */
bool	expand_redirections(t_node *node, t_shell *shell)
{
	t_redirection	*redir;
	char			*expanded;

	redir = node->redirections;
	while (redir)
	{
		if (redir->quote_type != QUOTE_SINGLE)
		{
			expanded = expand_one_arg(redir->target, shell);
			if (!expanded)
				return (false);
			free(redir->target);
			redir->target = expanded;
		}
		redir = redir->next;
	}
	return (true);
}

bool	expand_all(t_node *node, t_shell *shell)
{
	if (!remove_empty_args(node))
		return (perror("error removing expansion"), false);
	if (!expand_redirections(node, shell))
	{
		perror("Error rexpanding redirections");
		return (false);
	}
	if (node->args && !expand_wildcard(node))
	{
		perror("Error expanding wildcard *");
		return (false);
	}
	return (true);
}
