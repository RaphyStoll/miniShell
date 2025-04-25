/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:56:09 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/25 15:24:01 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "minishell.h"
#include "debbug.h"

/**
 * @brief Opens the file for a redirection.
 *
 * Handles IN, OUT, APPEND, and HEREDOC types.
 *
 * @param redir Redirection info.
 * @param env Environment list (for heredoc).
 * @return File descriptor or -1 on error.
 */
int	open_redirection_file(t_redirection *redir)
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
bool	single_redirection(t_redirection *redir)
{
	int	fd;
	int	target_fd;
	int	type;

	type = redir->type;
	if (type == REDIRECTION_IN || type == REDIRECTION_HEREDOC)
		target_fd = STDIN_FILENO;
	else if (type == REDIRECTION_OUT || type == REDIRECTION_APPEND)
		target_fd = STDOUT_FILENO;
	fd = open_redirection_file(redir);
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
bool	apply_redirections(t_redirection *redir)
{
	while (redir)
	{
		if (!single_redirection(redir))
			return (false);
		redir = redir->next;
	}
	return (true);
}
