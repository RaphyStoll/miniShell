/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:40:45 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/04 14:57:03 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"


/**
 * @brief Expands variables in redirection targets.
 *
 * Replaces variables like $VAR or $? in redirection targets,
 * except when the target is surrounded by single quotes.
 *
 * @param node The AST command node containing redirections.
 * @param env Environment variable list.
 */
void	expand_redirections(t_node *node, t_env *env)
{
	t_redirection	*redir;
	char			*expanded;

	redir = node->redirections;
	while (redir)
	{
		if (redir->quote_type != QUOTE_SINGLE)
		{
			expanded = expand_one_arg(redir->target, env);
			free(redir->target);
			redir->target = expanded;
		}
		redir = redir->next;
	}
}

/**
 * @brief Expands variables in command arguments based on quote type.
 *
 * Only arguments without quotes or with double quotes will be expanded.
 * Arguments inside single quotes are left untouched.
 *
 * @param node AST command node whose arguments may be expanded.
 * @param env Environment variable list 
 */
void	expand_variables(t_node *node, t_env *env)
{
	char	**args;
	char	*new_arg;
	int		quote_type;
	int		i;

	i = 0;
	args = node->args;
	while (args[i])
	{
		quote_type = node->arg_quotes[i];
		if (quote_type == QUOTE_NONE || quote_type == QUOTE_DOUBLE)
		{
			new_arg = expand_one_arg(args[i], env);
			free(args[i]);
			args[i] = new_arg;
		}
		i++;
	}
