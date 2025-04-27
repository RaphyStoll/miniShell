/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:59:37 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/27 15:56:43 by Charlye          ###   ########.fr       */
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
		if (!input || ft_strcmp(input, redir->target) == 0)
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

void	heredoc_child(t_redirection *redir, t_shell *shell)
{
	int					fd;
	struct sigaction	old;

	set_heredoc_signals(&old);
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("heredoc");
		exit (1);
	}
	if (!write_heredoc_lines(fd, redir, shell))
		exit(1);
	restore_signals(&old);
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
	pid_t	pid;
	int		fd;

	pid = fork();
	if (pid < 0)
		return (perror("fork"), -1);
	if (pid == 0)
		heredoc_child(redir, shell);
	shell->last_exit_status = handle_parent_process(pid, shell);
	if (g_signal == SIGINT)
		return (-1);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		perror("heredoc reopen");
	return (fd);
}

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

bool	prepare_heredocs_ast(t_node *node, t_shell *shell)
{
	if (!node)
		return (true);
	if (node->type == AST_COMMAND)
		prepare_heredocs(node->redirections, shell);
	if (node->type == AST_PIPE || node->type == AST_LOGICAL)
		return (prepare_heredocs_ast(node->child, shell)
			&& prepare_heredocs_ast(node->brother, shell));
	if (node->type == AST_SUBSHELL)
		return (prepare_heredocs_ast(node->child, shell));
	return (true);
}
