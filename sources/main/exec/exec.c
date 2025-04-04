/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:20:29 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/04 18:16:17 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	execute_ast(t_node *ast_node, t_shell *shell)
{
	int	status;

	if (!shell->ast)
		return (1);
	status = 0;
	if (ast_node->type == AST_COMMAND)
	{
		expand_variable(ast_node, shell->env);
		expand_redirections(ast_node, shell->env);
		status = execute_command(ast_node, shell);
	}
	else if (ast_node->type == AST_PIPE)
		status = execute_pipe(ast_node, shell);
	else if (ast_node->type == AST_LOGICAL)
		status = execute_logical(ast_node, shell);
	else if (ast_node->type == AST_SUBSHELL)
		status = execute_subshell(ast_node, shell);
	else
		status = 1;
	shell->last_exit_status = status;
	return (status);
}