/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:56:20 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/16 22:39:52 by raphaelferr      ###   ########.fr       */
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
bool	builtin_export(t_env **env, char *arg);

bool	is_valid_identifier(const char *str);
t_env	*find_node(t_env *env, char *var_name);
t_env	*get_last_node(t_env *dup_env);
bool	env_update(t_env **env, t_env *new_node);
void append_node(t_env **env, t_env *new_node);
void	remplace_node(t_env **env, t_env *old_node, t_env *new_node);
bool	pars_arg(t_env **env, char *arg);
void	display_export(t_env *env);
bool	handle_assignment(t_env **env, t_env *new_node, bool append);
#endif