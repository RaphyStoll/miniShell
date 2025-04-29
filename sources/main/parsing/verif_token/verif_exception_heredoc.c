/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_exception_heredoc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:31:44 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/29 18:24:24 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_struct.h"
#include "minishell.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>


bool	heredoc_child_exception(t_token *token)
{
	char	*line;
	char	*delimiter;

	if (!token->next || token->next->type != WORD)
		return (perror("minishell"), false);
	delimiter = token->next->str;
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0 || g_signal == SIGINT)
		{
			free(line);
			if (g_signal == SIGINT)
				return (g_signal = 0, false);
			break ;
		}
		free(line);
	}
	return (true);
}

int	handle_heredoc_exception(t_shell *shell, t_token *token)
{
	pid_t				pid;
	struct sigaction	old;

	ignore_heredoc_signals(&old);
	pid = fork();
	if (pid == -1)
		return (perror("fork heredoc exception"), GENERIC_ERROR);
	else if (pid == 0)
	{
		set_heredoc_signals(&old);
		if (heredoc_child_exception(token))
			exit (SUCCESS);
		else
			exit (GENERIC_ERROR);
	}
	shell->last_exit_status = handle_parent_process(pid, shell);
	restore_signals(&old);

	return (shell->last_exit_status);
}
