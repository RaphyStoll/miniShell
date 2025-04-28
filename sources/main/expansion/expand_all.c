/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:40:45 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/28 14:55:14 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "debbug.h"

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
	j= 0;

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

/**
 * @brief Expands variables in command arguments based on quote type.
 *
 * Only arguments without quotes or with double quotes will be expanded.
 * Arguments inside single quotes are left untouched.
 *
 * @param node AST command node whose arguments may be expanded.
 * @param env Environment variable list
 * @return ture if expansion succeeded for all arguemnts else false
 */
bool	expand_variables(t_node *node, t_shell *shell)
{
	char	**args;
	char	*new_arg;
	int		quote_type;
	int		i;

	if (!node || !shell || !node->args || !node->arg_quotes)
		return (false);
	i = 0;
	args = node->args;
	while (args[i])
	{
		quote_type = node->arg_quotes[i];
		if (quote_type == QUOTE_NONE || quote_type == QUOTE_DOUBLE)
		{
			new_arg = expand_one_arg(args[i], shell);
			if (!new_arg)
				return (false);
			free(args[i]);
			args[i] = new_arg;
		}
		i++;
	}
	return (true);
}

bool	expand_all(t_node *node, t_shell *shell)
{
	// if (!expand_variables(node, shell))
	// {
	// 	perror("Error expanding variables");
	// 	return (false);
	// }
	if (!remove_empty_args(node))
		return (perror("error removing expansion"), false);
	if (!expand_redirections(node, shell))
	{
		perror("Error rexpanding redirections");
		return (false);
	}
	if (!expand_wildcard(node))
	{
		perror("Error expanding wildcard *");
		return (false);
	}
	return (true);
}
