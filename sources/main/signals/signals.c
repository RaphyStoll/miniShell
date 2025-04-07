/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:53:41 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/07 10:55:56 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

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

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
		g_signal = signal;
}

// SIGINT : Ctrl + C  //
// SIGQUIT : Ctrl + \ //

void	set_signals(void)
{
	struct sigaction	sa;

	// sa.sa_handler = sigint_handler;
	// sigemptyset(&sa.sa_mask);
	// sa.sa_flags = 0;
	// sigaction(SIGINT, &sa, NULL);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ignore_ctrl_display(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

