/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:20:08 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/28 13:28:55 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

/**
 * @brief Signal handler for SIGINT during heredoc input.
 *
 * This handler is used to catch Ctrl+C while reading a heredoc.
 * It prints a newline and exits with status 130, as expected by Bash.
 *
 * @param sig The signal number (unused).
 */
void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

/**
 * @brief Restores the previous signal handler for SIGINT.
 *
 * Used after heredoc input to reset the signal behavior back
 * to the default shell handler.
 *
 * @param old Pointer to the previous sigaction structure to restore.
 */
void	restore_signals(struct sigaction *old)
{
	sigaction(SIGINT, old, NULL);
	signal(SIGQUIT, SIG_DFL);
}

/**
 * @brief Sets a custom signal handler for SIGINT during heredoc.
 *
 * Installs a new handler to properly manage Ctrl+C while reading heredoc input.
 * Previous handler is stored as to be restored later.
 *
 * @param old Pointer to store the previous sigaction structure.
 */
void	set_heredoc_signals(struct sigaction *old)
{
	struct sigaction	new;

	new.sa_handler = heredoc_sigint_handler;
	new.sa_flags = 0;
	sigemptyset(&new.sa_mask);
	sigaction(SIGINT, &new, old);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_heredoc_signals(struct sigaction *old)
{
	struct sigaction	ignore;

	ignore.sa_handler = SIG_IGN;
	ignore.sa_flags = 0;
	sigemptyset(&ignore.sa_mask);
	sigaction(SIGINT, &ignore, old);
	signal(SIGQUIT, SIG_IGN);
}
