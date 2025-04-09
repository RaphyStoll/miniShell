/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:16:34 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/09 12:09:58 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Executes the second command in the pipe chain.
 *
 * This function creates a new child process for the second part of the pipe.
 * It redirects the input from the pipe and executes the second command.
 *
 * @param pipe_fd The file descriptors for the pipe (read and write).
 * @param pipe AST node for the pipe.
 * @param shell The shell context containing the environment and exit status.
 * @return 0 on success, or 1 if an error occurs.
 */
int	execute_pipe_brother(int pipe_fd[2], t_node *pipe, t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork after pipe");
		return (1);
	}
	else if (pid == 0)
	{
		redirect_input_from_pipe(pipe_fd);
		execute_child_process(pipe->brother, shell);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		handle_parent_process(pid, shell);
	}
	return (0);
}

/**
 * @brief Redirects the input of the command from the pipe.
 *
 * Redirects the stdin of the process to the read-end of the pipe.
 *
 * @param pipefd File descriptors of the pipe (read and write).
 * @return 0 on success, -1 on failure.
 */
void	redirect_input_from_pipe(int pipe_fd[2])
{
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 input redirection failed");
		exit(GENERIC_ERROR);
	}
}

/**
 * @brief Redirects the output of the command to the pipe.
 *
 * Redirects the stdout of the process to the write-end of the pipe.
 *
 * @param pipefd File descriptors of the pipe (read and write).
 * @return 0 on success, -1 on failure.
 */
void	redirect_output_to_pipe(int pipe_fd[2])
{
	if (dup2(pipe_fd[1], STDOUT_FILENO) == -1)
	{
		perror("dup2 output redirection failed");
		exit (GENERIC_ERROR);
	}
}

/**
 * @brief Creates a pipe and stores the read and write fd in pipe_fd.
 * If fails, reports the error and updates the shell's exit status.
 *
 * @param pipe_fd File descriptors of the pipe (read and write).
 * @param shell The shell context containing the exit status.
 * @return 0 on success, 1 on failure.
 */
int	create_pipe(int pipe_fd[2], t_shell *shell)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe creation failed");
		shell->last_exit_status = GENERIC_ERROR;
		return (1);
	}
	return (0);
}

/**
 * @brief Executes a command with a pipe.
 *
 * @param pipe AST node for the pipe.
 * @param shell The shell context.
 * @return 0 on success, 1 on failure.
 */
int	execute_pipe(t_node *pipe, t_shell *shell)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (create_pipe(pipe_fd, shell) != 0)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		shell->last_exit_status = GENERIC_ERROR;
		exit (GENERIC_ERROR);
	}
	else if (pid == 0)
	{
		redirect_output_to_pipe(pipe_fd);
		execute_child_process(pipe->child, shell);
	}
	else
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (execute_pipe_brother(pipe_fd, pipe, shell));
	}
}
