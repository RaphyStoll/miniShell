/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 14:56:20 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/16 18:40:37 by raphalme         ###   ########.fr       */
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
bool	pars_arg(t_env *env, char *arg);

bool	is_valid_identifier(const char *str);
t_env	*add_env_node2(t_env **env_list, t_env *new_node);
t_env	*find_env(t_env *env, char *var_name);

#endif