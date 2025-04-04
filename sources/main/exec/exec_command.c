/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:01:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/04 18:12:50 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_var;
	char	*cmd_path;
	int		i;

	path_var = get_env_value(env, "PATH");
	if (!path_var)
		return (NULL);
	paths = ft_split(path_var, ';');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

void	execute_child_process(t_node *cmd, t_shell *shell)
{
	pid_t	pid;
	char	*cmd_path;
	char	**envp;

	if (!apply_redirections(cmd->redirections))
		exit (1);
	envp = get_envp(shell->env);
	cmd_path = find_cmd_path(cmd->args[0], shell->env);
	execve(cmd_path, cmd->args, envp);

}

int	handle_parent_process(pid_t pid, t_shell *shell)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		shell->last_exit_status = 128 + WTERMSIG(status);
	return (shell->last_exit_status);
}

int	execute_command(t_node *cmd, t_shell *shell)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0])
		return (1);
	if (is_builtin(cmd->args[0]))
	{
		shell->last_exit_status = execute_builtin(cmd->args, shell);
		return (shell->last_exit_status);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	else if (pid == 0)
		execute_child_process(cmd, shell);
	else
		return (handle_parent_process(pid, shell));
}
