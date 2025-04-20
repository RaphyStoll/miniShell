/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:56:20 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/21 00:44:35 by raphaelferr      ###   ########.fr       */
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
void	builtin_exit(t_shell *shell, int error, char *arg);

//! export
bool	builtin_export(t_env **env, char *arg);
bool	env_update(t_env **env, t_env *new_node);
bool	pars_arg(t_env **env, char *arg);
bool	handle_assignment(t_env **env, t_env *new_node, bool append);
void	display_export(t_env *env);

//! export utils
bool	is_valid_identifier(const char *str);
t_env	*find_node(t_env *env, char *var_name);
bool	parse_key_value(char *arg, char **key, char **value, bool *append);

#endif