/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:57:57 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/04 21:10:57 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string.h>
# include <unistd.h>
# include "colors.h"
# include "lexing_struct.h"
# include "minishell.h"

//! Error handling
void	nbr_error(t_error error_code, char *message);
t_token	*ft_exit_error(t_token *tokens, t_error code, char *error_token);
void	print_error_message(t_error code, char *error_token);

//! Memory utils
void	free_all(t_token *token);
void	free_tokens(t_token *head);
void free_env(t_env *head);

//! free ast

void	free_redirections(t_redirection *redir);
void	free_args(char **args);
void	free_all_ast(t_node *ast);
void	free_node(t_node *node);

//! lst_utils
t_env	*env_dup(t_env *src);

//!mege sort
t_env *sorted_merge(t_env *a, t_env *b);
void split_list(t_env *source, t_env **front, t_env **back);
void sort_env(t_env **head_ref);

#endif