/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:56:09 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/17 13:51:11 by chpasqui         ###   ########.fr       */
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
		input = readline("> ");
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
	int					fd;
	struct sigaction	old_sa;

	set_heredoc_signals(&old_sa);
	printf("je suis dans handle_heredoc");
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		restore_signals(&old_sa);
		return (-1);
	}
	if (!write_heredoc_lines(fd, redir, shell))
	{
		close(fd);
		restore_signals(&old_sa);
		return (-2);
	}
	close(fd);
	restore_signals(&old_sa);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd == -1)
		perror("heredoc reopen");
	unlink(".heredoc_tmp");
	return (fd);
}

/**
 * @brief Opens the file for a redirection.
 *
 * Handles IN, OUT, APPEND, and HEREDOC types.
 *
 * @param redir Redirection info.
 * @param env Environment list (for heredoc).
 * @return File descriptor or -1 on error.
 */
int	open_redirection_file(t_redirection *redir, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (!redir || !redir->target)
		return (-1);
	if (redir->type == REDIRECTION_IN)
		fd = open(redir->target, O_RDONLY);
	else if (redir->type == REDIRECTION_OUT)
		fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIRECTION_APPEND)
		fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIRECTION_HEREDOC)
		fd = handle_heredoc(redir, shell);
	return (fd);
}

/**
 * @brief Applies one redirection using dup2. 
 * 
 * Redirects STDIN or STDOUT as needed.
 *
 * @param redir Redirection to apply.
 * @param env Environment list.
 * @return true on success, false on error.
 */
bool	single_redirection(t_redirection *redir, t_shell *shell)
{
	int	fd;
	int	target_fd;
	int	type;

	type = redir->type;
	if (type == REDIRECTION_IN || type == REDIRECTION_HEREDOC)
		target_fd = STDIN_FILENO;
	else if (type == REDIRECTION_OUT || type == REDIRECTION_APPEND)
		target_fd = STDOUT_FILENO;
	fd = open_redirection_file(redir, shell);
	if (fd == -2)
		return (false);
	if (fd == -1)
		return (perror(redir->target), false);
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

/**
 * @brief Applies a list of redirections.
 *
 * Stops at the first failure.
 *
 * @param redir Redirection list.
 * @param env Environment list.
 * @return true on success, false otherwise.
 */
bool	apply_redirections(t_redirection *redir, t_shell *shell)
{
	while (redir)
	{
		if (!single_redirection(redir, shell))
			return (false);
		redir = redir->next;
	}
	return (true);
}
