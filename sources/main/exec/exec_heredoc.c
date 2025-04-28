/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:59:37 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/28 14:09:50 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"

/**
 * @brief Reads heredoc input and writes it to a file.
 *
 * Expands variables if not quoted. Stops at the delimiter.
 *
 * @param fd File descriptor to write to.
 * @param redir Heredoc info (target, quote).
 * @param env Environment list.
 * @return true on success, false on malloc error.
 */
bool	write_heredoc_lines(int fd, t_redirection *redir, t_shell *shell)
{
	char	*input;
	char	*line;

	while (1)
	{
		input = readline("heredoc> ");
		if (!input)
			return (false);
		if (ft_strcmp(input, redir->target) == 0)
		{
			free(input);
			break ;
		}
		if (redir->quote_type == QUOTE_NONE)
			line = expand_one_arg(input, shell);
		else
			line = ft_strdup(input);
		free(input);
		if (!line)
			return (false);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	return (true);
}

/**
 * @brief Child process to read a here-doc into a temp file.
 *
 * Opens the temp file, calls write_heredoc_lines(),
 * then exits with 0 or 1 on error.
 * 
 * @param redir   Redirection info containing the delimiter.
 * @param shell   Shell context for variable expansion.
 */
void	heredoc_child(t_redirection *redir, t_shell *shell)
{
	int					fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		exit (1);
	}
	if (!write_heredoc_lines(fd, redir, shell))
		exit(1);
	close(fd);
	exit(0);
}

/**
 * @brief Handles heredoc input and returns a read fd.
 *
 * Writes to a temp file, then reopens it for reading.
 *
 * @param redir Heredoc info.
 * @param env Environment list.
 * @return Read fd or -1 on error.
 */
int	handle_heredoc(t_redirection *redir, t_shell *shell)
{
	pid_t				pid;
	int					fd;
	struct sigaction	old;

	ignore_heredoc_signals(&old);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
	{
		set_heredoc_signals(&old);
		heredoc_child(redir, shell);
	}
	shell->last_exit_status = handle_parent_process(pid, shell);
	restore_signals(&old);
	if (g_signal == SIGINT)
	{
		unlink(".heredoc_tmp");
		return (-1);
	}
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		perror("heredoc reopen");
	return (fd);
}

/**
 * @brief Prepare here-docs in a redirection list.
 * 
 * Reads each here-doc, writes it to a temp file,
 * then rewrites the redirection to that file.
 *
 * @param redir   List of redirections to process.
 * @param shell   Shell context (status, env, etc.).
 * @return true on success, false on error.
 */
bool	prepare_heredocs(t_redirection *redir, t_shell *shell)
{
	int	fd;

	while (redir)
	{
		if (redir->type == REDIRECTION_HEREDOC)
		{
			fd = handle_heredoc(redir, shell);
			if (fd < 0)
				return (false);
			close(fd);
			redir->type = REDIRECTION_IN;
			free(redir->target);
			redir->target = strdup(".heredoc_tmp");
			if (!redir->target)
				return (false);
		}
		redir = redir->next;
	}
	return (true);
}

/**
 * @brief Recursively prepare here-docs in an AST.
 *
 * Traverses commands, pipes, logical ops and subshells,
 * calling prepare_heredocs on each command’s redirs.
 * 
 * @param node    Root of the AST (or subtree).
 * @param shell   Shell context passed to prepare_heredocs.
 * @return true if all here-docs succeeded, false otherwise.
 */
bool	prepare_heredocs_ast(t_node *node, t_shell *shell)
{
	if (!node)
		return (true);
	if (node->type == AST_COMMAND)
	{
		if (node->redirections)
		{
			if (!prepare_heredocs(node->redirections, shell))
				return (false);
		}
	}
	else if (node->type == AST_PIPE || node->type == AST_LOGICAL)
	{
		if (!prepare_heredocs_ast(node->child, shell))
			return (false);
		if (!prepare_heredocs_ast(node->brother, shell))
			return (false);
	}
	else if (node->type == AST_SUBSHELL)
	{
		if (!prepare_heredocs_ast(node->child, shell))
			return (false);
	}
	return (true);
}
