/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:25:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/21 00:41:10 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"
#include "utils.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>

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

static bool	handle_heredoc(t_token *token)
{
	char				*line;
	char				*delimiter;

	if (!token->next || token->next->type != WORD)
		return (perror("minishell"), false);
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

static int	run_pipe(t_token *token)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), GENERIC_ERROR);
	if (pid == 0)
	{
		if (handle_heredoc(token))
			exit (SUCCESS);
		else
			exit (GENERIC_ERROR);
	}
	if (waitpid(pid, &status, 0) == 0)
	{
		perror("waitpid");
		return (GENERIC_ERROR);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

bool	handle_redirection_exceptions(t_token *token, int *flag)
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
		return (run_pipe(token));
	return (true);
}
