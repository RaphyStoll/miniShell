/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:53:41 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/12 19:08:50 by Charlye          ###   ########.fr       */
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
 * @brief Handles SIGINT after it has been captured.
 *
 * If the global signal variable is set to SIGINT, this function resets
 * the prompt line by writing a newline, clearing the current input, 
 * and redisplaying the prompt.
 * 
 * To be called after `readline()` returns.
 */
void	handle_signals(void)
{
	if (g_signal == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 0;
	}
}

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
		g_signal = signal;
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
	signal(SIGINT, sigint_handler);
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

// int	main(void)
// {
// 	char *input;

// 	set_signals();
// 	ignore_ctrl_display();
// 	rl_catch_signals = 0;
// 	while (1)
// 	{
// 		input = readline("test$ ");
// 		if (!input)
// 		{
// 			if (g_signal == SIGINT)
// 			{
// 				handle_signals(); // réaffiche proprement le prompt
// 				continue;
// 			}
// 			printf("exit\n");
// 			break;
// 		}
// 		handle_signals(); // au cas où SIGINT est arrivé après readline
// 		if (*input)
// 			add_history(input);
// 		free(input);
// 	}
// 	rl_clear_history();
// 	return (0);
// }
