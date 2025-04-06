/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:51:34 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/04 14:55:22 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "env_struct.h"
# include "ast_struct.h"

void	expand_variables(t_node *node, t_env *env);
void	expand_redirections(t_node *node, t_env *env);
char	*expand_one_arg(char *arg, t_env *env);
int		handle_variable(char **result, char *arg, int *i, t_env *env);
int		handle_regular_char(char **result, char c);
int		handle_exit_status(char **result);

#endif
