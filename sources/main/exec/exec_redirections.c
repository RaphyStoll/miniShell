/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 11:56:09 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/07 12:54:01 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	open_redirection_file(t_redirection *redir)
{
	int	fd;

	if (redir->type == REDIRECTION_IN)
		fd = open(redir->target, O_RDONLY);
	else if (redir->type == REDIRECTION_OUT)
		fd = open(redir->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == REDIRECTION_APPEND)
		fd = open(redir->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == REDIRECTION_HEREDOC)
		fd = handle_heredoc(redir);
	return (fd);
}

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
	if (fd == -1)
	{
		perror(redir->target);
		return (false);
	}
	if (dup2(fd, target_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

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
