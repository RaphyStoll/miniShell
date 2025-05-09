/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:15:50 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/17 12:07:32 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

/**
 * @brief Executes a subshell by forking a new process.
 *
 * Executes the command in a subshell. If fork fails, returns a generic error.
 * The parent process waits for the child and handles the exit status.
 *
 * @param subshell AST node representing the subshell command.
 * @param shell Shell context.
 * @return Exit status of the subshell process.
 */
int	execute_subshell(t_node *subshell, t_shell *shell)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (perror("fork subshell failed"), GENERIC_ERROR);
	else if (pid == 0)
	{
		status = execute_ast(subshell->child, shell);
		return (status);
	}
	else
	{
		status = handle_parent_process(pid, shell);
		exit(SUCCESS);
	}
}
