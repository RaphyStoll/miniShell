/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:40:45 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/20 20:46:18 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"

bool	expand_wildcard(t_node *node, t_shell *shell)
{
	int		i;
	int		files_count;
	char	**new;

	
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
	if (!expand_variables(node, shell))
	{
		perror("Error expanding variables");
		return (false);
	}
	if (!expand_redirections(node, shell))
	{
		perror("Error rexpanding redirections");
		return (false);
	}
	if (!expand_wildcard(node, shell))
	{
		perror("Error expanding wildcard *");
		return (false);
	}
	return (true);
}
