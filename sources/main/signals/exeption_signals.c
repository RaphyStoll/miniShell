/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exeption_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:20:08 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/17 16:58:52 by chpasqui         ###   ########.fr       */
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
void	exception_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g_signal = SIGINT;
}

/**
 * @brief Sets a custom signal handler for SIGINT during heredoc.
 *
 * Installs a new handler to properly manage Ctrl+C while reading heredoc input.
 * Previous handler is stored as to be restored later.
 *
 * @param old Pointer to store the previous sigaction structure.
 */
void	set_exception_signals(struct sigaction *old)
{
	struct sigaction	new_e;

	new_e.sa_handler = exception_sigint_handler;
	new_e.sa_flags = 0;
	sigemptyset(&new_e.sa_mask);
	sigaction(SIGINT, &new_e, old);
}
