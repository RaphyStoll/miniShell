/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:20:29 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/01 12:12:34 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

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
	if (!shell->ast)
		return (1);
	if (!prepare_heredocs_ast(ast_node, shell))
		return (shell->last_exit_status);
	if (ast_node->type == AST_COMMAND)
	{
		if (!expand_all(ast_node, shell))
			return (shell->last_exit_status = GENERIC_ERROR);
		shell->last_exit_status = execute_command(ast_node, shell);
	}
	else if (ast_node->type == AST_PIPE)
		shell->last_exit_status = execute_pipe(ast_node, shell);
	else if (ast_node->type == AST_LOGICAL)
		shell->last_exit_status = execute_logical(ast_node, shell);
	else if (ast_node->type == AST_SUBSHELL)
		shell->last_exit_status = execute_subshell(ast_node, shell);
	else
		shell->last_exit_status = GENERIC_ERROR;
	return (shell->last_exit_status);
}
