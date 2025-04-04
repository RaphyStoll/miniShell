/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:01:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/04 16:02:27 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute_child_process(t_node *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*cmd_path;
	char	**envp;

}

void	handle_parent_process(t_shell *shell)
{
	
}

void	execute_command(t_node *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return ;
	if (is_builtin(cmd->args[0]))
	{
		shell->last_exit_status = execute_builtin(cmd->args, shell->env);
		return ;
	}
	execute_child_process(cmd, shell);
	handle_parent_process(shell);
}
