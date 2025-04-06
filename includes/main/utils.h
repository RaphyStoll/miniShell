/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:57:57 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/06 14:57:02 by raphaelferr      ###   ########.fr       */
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
t_token	*ft_exit_error(t_token *tokens, t_error_code code, char *error_token);
void	print_error_message(t_error_code code, char *error_token);

//! Memory utils
void	free_all(t_token *token);
void	free_tokens(t_token *head);
void	free_env(t_env *head);

//! free ast

void	free_redirections(t_redirection *redir);
void	free_args(char **args);
void	free_all_ast(t_node *ast);
void	free_node(t_node *node);

#endif