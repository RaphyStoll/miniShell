/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:15:50 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/14 14:07:44 by Charlye          ###   ########.fr       */
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
	{
		perror("fork subshell failed");
		return (GENERIC_ERROR);
	}
	else if (pid == 0)
	{
		free(shell->prompt);
		shell->prompt = ft_strdup("(subshell) minishell-0.8$ ");
		if (!shell->prompt)
		{
			perror("strdup failed of prompt subshell");
			exit(GENERIC_ERROR);
		}
		status = execute_ast(subshell->child, shell);
		return (status);
	}
	else
		return (handle_parent_process(pid, shell));
}
