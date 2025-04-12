/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:56:20 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/12 22:11:57 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/errno.h>
# include "env_struct.h"
# include "minishell.h"

int		builtin_pwd(void);
int		builtin_cd(t_shell *shell, char **args);
int		builtin_unset(t_shell *shell, char **args);
int		builtin_echo(char **args);
int		builtin_env(t_env *env);
void	builtin_exit(t_shell *shell, int error);
void	builtin_export(t_env *env);
bool	is_valid_identifier(const char *str);

#endif