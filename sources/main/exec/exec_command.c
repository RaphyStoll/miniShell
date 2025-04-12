/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:01:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/12 18:22:28 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

/**
 * @brief Searches for an executable command in a list of paths.
 *
 * @param paths Array of directory paths.
 * @param cmd Command name to search.
 * @return Full path to the executable or NULL if not found.
 */
char	*check_all_paths(char **paths, char *cmd)
{
	char	*tmp;
	char	*cmd_path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (free_array(paths), NULL);
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!cmd_path)
			return (free_array(paths), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (free_array(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Finds the full path of a command.
 *
 * @param cmd Command to resolve.
 * @param env Environment list to get PATH from.
 * @return Full path or NULL if not found.
 */
char	*find_cmd_path(char *cmd, t_shell *shell)
{
	char	**paths;
	char	*path_var;
	char	*cmd_path;

	path_var = get_env_value(shell, "PATH");
	if (!path_var)
		return (NULL);
	if (access(cmd, X_OK) == 0
		&& (cmd[0] == '/' || ft_strncmp(cmd, "./", 2) == 0
			|| ft_strncmp(cmd, "../", 3) == 0))
		return (ft_strdup(cmd));
	paths = ft_split(path_var, ':');
	if (!paths)
		return (NULL);
	cmd_path = check_all_paths(paths, cmd);
	free_array(paths);
	return (cmd_path);
}

/**
 * @brief Executes a command in the child process.
 *
 * Applies redirections, resolves the command path,
 * and calls execve. Exits with the appropriate code on failure.
 *
 * @param cmd AST command node.
 * @param shell Shell context with environment.
 */
void	execute_child_process(t_node *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;

	if (!apply_redirections(cmd->redirections, shell->env))
		exit (GENERIC_ERROR);
	envp = get_envp(shell->env);
	cmd_path = find_cmd_path(cmd->args[0], shell);
	if (!cmd_path)
	{
		free_array(envp);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
		exit (COMMAND_NOT_FOUND);
	}
	if (execve(cmd_path, cmd->args, envp) == -1)
	{
		free(cmd_path);
		free_array(envp);
		perror(cmd->args[0]);
		exit (PERMISSION_ERROR);
	}
}

/**
 * @brief Waits for a child process and updates shell status.
 *
 * Updates shell->last_exit_status and g_signal based on exit or signal.
 *
 * @param pid PID of the child to wait for.
 * @param shell Shell context.
 * @return Exit status of the child.
 */
int	handle_parent_process(pid_t pid, t_shell *shell)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		return (GENERIC_ERROR);
	}
	if (WIFEXITED(status))
	{
		shell->last_exit_status = WEXITSTATUS(status);
		g_signal = 0;
	}
	else if (WIFSIGNALED(status))
	{
		shell->last_exit_status = 128 + WTERMSIG(status);
		g_signal = WTERMSIG(status);
	}
	return (shell->last_exit_status);
}

/**
 * @brief Executes a single command (builtin or external).
 *
 * Forks a child process for external commands.
 * Handles builtins in the parent.
 *
 * @param cmd AST command node.
 * @param shell Shell context.
 * @return Exit status of the command.
 */
int	execute_command(t_node *cmd, t_shell *shell)
{
	pid_t	pid;

	if (!cmd || !cmd->args || !cmd->args[0] || !cmd->args[0][0])
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
		return (GENERIC_ERROR);
	}
	else if (pid == 0)
	{
		execute_child_process(cmd, shell);
		exit (GENERIC_ERROR);
	}
	else
		return (handle_parent_process(pid, shell));
}
