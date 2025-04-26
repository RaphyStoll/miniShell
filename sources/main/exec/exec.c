/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:20:29 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/26 16:15:36 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "debbug.h"

/**
 * @brief Executes an AST node.
 *
 * Based on the type of node (command, pipe, logical, subshell),
 * it executes the appropriate function to handle the node.
 *
 * @param ast_node AST node to execute.
 * @param shell Shell context.
 * @return Exit status of the command executed.
 */
int	execute_ast(t_node *ast_node, t_shell *shell)
{
	int	status;

	if (!shell->ast)
		return (1);
	status = 0;
	if (ast_node->type == AST_COMMAND)
	{
		if (!expand_all(ast_node, shell))
		{
			shell->last_exit_status = GENERIC_ERROR;
			return (shell->last_exit_status);
		}
		status = execute_command(ast_node, shell);
	}
	else if (ast_node->type == AST_PIPE)
		status = execute_pipe(ast_node, shell);
	else if (ast_node->type == AST_LOGICAL)
		status = execute_logical(ast_node, shell);
	else if (ast_node->type == AST_SUBSHELL)
		status = execute_subshell(ast_node, shell);
	else
		status = GENERIC_ERROR;
	shell->last_exit_status = status;
	return (status);
}
