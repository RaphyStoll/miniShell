/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_token.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:47:14 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/25 19:48:06 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERIF_TOKEN_H
# define VERIF_TOKEN_H
# include "lexing_struct.h"

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
bool	handle_redirection_exceptions(t_token *token_list);

#endif