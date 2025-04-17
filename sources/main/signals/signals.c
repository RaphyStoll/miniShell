/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:53:41 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/17 13:51:49 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/signals.h"
// #include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <termios.h>
#include <readline/readline.h>
#include <readline/history.h>

/**
 * @brief Signal handler function for SIGINT (Ctrl+C).
 *
 * This function sets the global signal indicator when SIGINT is received.
 * The actual handling (prompt update) is deferred to `handle_signals()`.
 *
 * @param signal The signal number (should be SIGINT).
 */
void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("je suis la");
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = signal;
	}
}

/**
 * @brief Sets up the default signal handlers for the shell.
 *
 * Installs a custom handler for SIGINT and ignores SIGQUIT.
 * SIGINT is redirected to 'sigint_handler' to the global signal variable.
 */
void	set_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Disables the display of control characters like ^C on the terminal.
 *
 * This modifies the terminal attributes to disable ECHOCTL,
 * preventing control characters from being printed when typed.
 */
void	ignore_ctrl_display(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

