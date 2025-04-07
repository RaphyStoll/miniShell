/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:01:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/07 11:52:28 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

char	*find_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*path_var;
	char	*cmd_path;

	path_var = get_env_value(env, "PATH");
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

void	execute_child_process(t_node *cmd, t_shell *shell)
{
	char	*cmd_path;
	char	**envp;

	if (!apply_redirections(cmd->redirections))
		exit (1);
	envp = get_envp(shell->env);
	cmd_path = find_cmd_path(cmd->args[0], shell->env);
	if (!cmd_path)
	{
		free_array(envp);
		write(2, cmd->args[0], ft_strlen(cmd->args[0]));
		write(2, ": command not found\n", 20);
		exit(127);
	}
	if (execve(cmd_path, cmd->args, envp) == -1)
	{
		free(cmd_path);
		free_array(envp);
		perror(cmd->args[0]);
		exit (126);
	}
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
		return (1);
	}
	else if (pid == 0)
		execute_child_process(cmd, shell);
	else
		return (handle_parent_process(pid, shell));
}
