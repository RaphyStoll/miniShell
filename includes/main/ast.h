/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:47:16 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/25 19:47:18 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include "colors.h"
# include "lexing_struct.h"
# include <stdlib.h>
# include "ast_struct.h"

//! utils
int		add_arg_to_node(t_node *node, char *arg);
t_node	*malloc_node(t_ast_type type);
int		handle_redirection(t_token **tokens, t_node *node);
void	add_redirection_to_node(t_node *node, t_redirection *redir);
t_node	*parse_command_or_subshell(t_token **tokens);

//! parse
t_node	*parse_logical(t_token **tokens);
t_node	*parse_command(t_token **tokens);
t_node	*parse_subshell(t_token **tokens);
t_node	*parse_pipe(t_token **tokens);

//! debbug
void	print_ast(t_node *node, int indent);
void	print_ast_debug(t_node *node, int level, const char *label);

//!free

void	free_redirections(t_redirection *redir);
void	free_args(char **args);
void	free_all_ast(t_node *ast);
void	free_node(t_node *node);
#endif