/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:29:12 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/07 10:10:11 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <signal.h>
# include <termios.h>
# include <readline/readline.h>

extern int	g_signal;

void	sigint_handler(int signal);
void	handle_signals(void);
void	set_signals(void);
void	ignore_ctrl_display(void);

#endif