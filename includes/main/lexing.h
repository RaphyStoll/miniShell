/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/04/28 18:24:07 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "lexing_struct.h"
# include "utils.h"
# include "minishell.h"

// Lexing
t_token	*lexer(t_shell *shell, const char *input);
t_token	*tokenizing(t_shell *shell, const char *input);

// Token
char	*handle_word(t_shell *shell, const char **input, t_quote *quote_type);
char	*get_quoted_word(const char **input, t_quote *quote_type);
char	*get_unquoted_word(const char **input);
char	*get_next_segment(const char **input, t_shell *shell, t_quote *quote);
char	*append_segment(char *word, char *seg);
bool	handle_operator(t_shell *shell, const char **input);
bool	add_operator(t_shell *shell, const char **input, t_type op);
t_token	*init_token(t_shell *shell, char *str, t_type op, t_quote quote_type);
bool	add_token(t_shell *shell, char *str, t_type op, t_quote quote_type);

// Synthax utils
bool	is_quote(char c);
t_type	is_operator(const char *input);
bool	is_symbol(char c);
bool	is_parenthesis(char c);
bool	is_forbidden_char(char c);

//Error handling
bool	check_unclosed_quotes(t_shell *shell, const char *input);
bool	check_unclosed_parentheses(t_shell *shell, const char *input);
void	free_all(t_token *token);

#endif