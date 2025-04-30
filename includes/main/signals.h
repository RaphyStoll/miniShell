/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:29:12 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/30 07:25:40 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>

extern int	g_signal;

void	sigint_handler(int signal);
void	handle_signals(void);
void	set_signals(void);
void	ignore_ctrl_display(void);

//signaux pour redirections
void	set_heredoc_signals(struct sigaction *old);
void	restore_signals(struct sigaction *old);
void	heredoc_sigint_handler(int sig);
void	ignore_heredoc_signals(struct sigaction *old);

#endif