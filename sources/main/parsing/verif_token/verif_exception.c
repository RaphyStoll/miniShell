/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:25:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/29 18:26:43 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"
#include <fcntl.h>
#include <stdio.h>

static bool	handle_redirect_in(t_token *token)
{
	if (!token->next)
		return (false);
	if (access(token->next->str, F_OK) != 0)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(token->next->str);
		return (false);
	}
	return (true);
}

static bool	handle_redirect_out(t_token *token)
{
	int	fd;
	int	flags;

	if (!token->next || token->next->type != WORD)
		return (perror("minishell"), false);
	if (token->type == REDIRECT_OUT)
		flags = O_WRONLY | O_CREAT | O_TRUNC;
	else
		flags = O_WRONLY | O_CREAT | O_APPEND;
	fd = open(token->next->str, flags, 0644);
	if (fd == -1)
	{
		perror("minishell: failed to open file");
		return (false);
	}
	close(fd);
	return (true);
}

bool	handle_redir_exceptions(t_shell *shell, t_token *token, int *flag)
{
	if (token->prev != NULL)
		return (true);
	if (token->type != REDIRECT_IN && token->type != REDIRECT_OUT
		&& token->type != APPEND && token->type != HEREDOC)
		return (true);
	if (!token->next || token->next->type != WORD)
		return (true);
	if (token->next->next != NULL)
		return (true);
	*flag = 1;
	if (!token)
		return (true);
	if (token->type == REDIRECT_IN)
		return (!(handle_redirect_in(token)));
	else if (token->type == REDIRECT_OUT || token->type == APPEND)
		return (handle_redirect_out(token));
	else if (token->type == HEREDOC)
		return (handle_heredoc_exception(shell, token));
	return (true);
}
