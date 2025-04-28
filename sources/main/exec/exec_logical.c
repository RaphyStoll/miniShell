/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:15:11 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/28 15:40:47 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

/**
 * @brief Executes logical operations (AND/OR) between two commands.
 *
 * Executes the left and right commands based on the logical operator (&& or ||).
 *
 * @param logic AST node representing the logical operation.
 * @param shell Shell context.
 * @return Exit status based on the execution of the logical operation.
 */
int	execute_logical(t_node *logic, t_shell *shell)
{
	if (logic->logic_type == LOGICAL_AND)
	{
		if (execute_ast(logic->child, shell) == 0)
			execute_ast(logic->brother, shell);
	}
	else if (logic->logic_type == LOGICAL_OR)
	{
		if (execute_ast(logic->child, shell) != 0)
			execute_ast(logic->brother, shell);
	}
	else
	{
		shell->last_exit_status = GENERIC_ERROR;
		return (shell->last_exit_status);
	}
	return (shell->last_exit_status);
}
