/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signals.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 16:20:08 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/07 16:26:07 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(130);
}

void	restore_signals(struct sigaction *old)
{
	sigaction(SIGINT, old, NULL);
}

void	set_heredoc_signals(struct sigaction *old)
{
	struct sigaction	new;

	new.sa_handler = heredoc_sigint_handler;
	new.sa_flags = SA_RESTART;
	sigemptyset(&new.sa_mask);
	sigaction(SIGINT, &new, old);
}
