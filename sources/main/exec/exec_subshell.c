/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:15:50 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/15 15:28:29 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

bool	modify_shell_level(t_shell *shell, bool increase)
{
	char	*new_shlvl;

	if (increase)
		shell->shell_level += 1;
	else if (shell->shell_level > 1)
		shell->shell_level -= 1;
	else
		return (true);
	new_shlvl = ft_itoa(shell->shell_level);
	if (!new_shlvl)
		return (perror("Failed to update SHLVL"), false);
	if (!set_env_value(&shell->env, "SHLVL", new_shlvl))
		return (perror("Failed to modify SHLVL"), free(new_shlvl), false);
	free(new_shlvl);
	return (true);
}

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

	if (!modify_shell_level(shell, true))
		return (GENERIC_ERROR);
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
		if (!modify_shell_level(shell, false))
			perror("failed to decrease shell level");
		return (status);
	}
}

