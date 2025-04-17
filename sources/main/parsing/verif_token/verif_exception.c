/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:25:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/17 16:52:41 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"
#include "signals.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/readline.h>

static bool	handle_redirect_in(t_token *token)
{
	if (!token->next || token->next->type != WORD)
	{
		perror("minishell");
		return (false);
	}
	if (access(token->next->str, F_OK) != 0)
	{
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
	{
		perror("minishell");
		return (false);
	}
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

static bool	handle_heredoc(t_token *token)
{
	char				*line;
	char				*delimiter;

	if (!token->next || token->next->type != WORD)
	{
		perror("minishell");
		return (false);
	}
	delimiter = token->next->str;
	signal(SIGINT, exception_sigint_handler);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0 || g_signal == SIGINT)
		{
			free(line);
			break ;
		}
		free(line);
	}
	signal(SIGINT, sigint_handler);
	if (g_signal == SIGINT)
	{
		g_signal = 0;
		return (false);
	}
	return (true);
}

bool	handle_redirection_exceptions(t_token *token)
{
	if (!token)
		return (true);
	if (token->type == REDIRECT_IN)
		return (handle_redirect_in(token));
	else if (token->type == REDIRECT_OUT || token->type == APPEND)
		return (handle_redirect_out(token));
	else if (token->type == HEREDOC)
		return (handle_heredoc(token));
	return (true);
}
