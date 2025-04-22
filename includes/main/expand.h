/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:51:34 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/22 15:33:37 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "env_struct.h"
# include "ast_struct.h"
# include "stdlib.h"

bool	expand_all(t_node *node, t_shell *shell);
bool	expand_variables(t_node *node, t_shell *shell);
bool	expand_redirections(t_node *node, t_shell *shell);
char	*expand_one_arg(char *arg, t_shell *shell);
bool	handle_variable(char **result, char *arg, int *i, t_shell *shell);
bool	handle_regular_char(char **result, char c);
bool	handle_exit_status(char **result, t_shell *shell);
bool	remove_empty_args(t_node *node);

#endif
