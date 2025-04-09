/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_logical.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:15:11 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/09 16:16:23 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
	if (logic->type == LOGICAL_AND)
	{
		if (execute_command(logic->child, shell) == 0)
			execute_command(logic->brother, shell);
	}
	else if (logic->type == LOGICAL_OR)
	{
		if (execute_command(logic->child, shell) != 0)
			execute_command(logic->brother, shell);
	}
	else
	{
		shell->last_exit_status = GENERIC_ERROR;
		return (shell->last_exit_status);
	}
	return (shell->last_exit_status);
}
