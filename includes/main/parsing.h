/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:18:02 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/21 00:44:57 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "lexing.h"
# include "error_code.h"
# include "colors.h"
# include "utils.h"
# include "../../lib/libft/header/libft.h"
# include "../../lib/libft/header/libft_bonus.h"

//!parsing
bool	init_parsing(t_token *tokens, int *flag);

//! debbug
void	print_tokens(t_token *head);
void	print_current_tokens(t_token *tokens);
void	print_tab(char **tab);
void	print_node(t_token *current);
void	print_list(t_token **head);
void	print_current_token(t_token *token);
void	print_ast(t_node *node, int indent);
void	print_redirections(t_redirection *redir, int indent);

//!token verif
bool	if_valide_token_prev(t_token *current);
bool	if_valide_token_next(t_token *current);
bool	valid_content(t_token *current);

//! verif pipe and word
bool	valid_type_pipe_prev(t_token *cur);
bool	valid_type_pipe_next(t_token *cur);
bool	valid_type_word_prev(t_token *cur);
bool	valid_type_word_next(t_token *cur);

//! verif redirect
bool	valid_type_redirect_in_prev(t_token *cur);
bool	valid_type_redirect_in_next(t_token *cur);
bool	valid_type_redirect_out_prev(t_token *cur);
bool	valid_type_redirect_out_next(t_token *cur);

//! verif And / or
bool	valid_type_and_prev(t_token *cur);
bool	valid_type_and_next(t_token *cur);
bool	valid_type_or_prev(t_token *cur);
bool	valid_type_or_next(t_token *cur);

//! verif heredoc et append
bool	valid_type_heredoc_prev(t_token *cur);
bool	valid_type_heredoc_next(t_token *cur);
bool	valid_type_append_prev(t_token *cur);
bool	valid_type_append_next(t_token *cur);

//! verif exception
bool	handle_redirection_exceptions(t_token *token, int *flag);

//!free
void	free_tokens(t_token *head);
void	free_all(t_token *token);
void	free_ast(t_node *node);
void	free_redirections(t_redirection *redir);

#endif