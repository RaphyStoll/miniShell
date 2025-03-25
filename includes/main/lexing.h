/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/25 19:48:02 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include "lexing_struct.h"
# include "utils.h"
# include "minishell.h"

// Lexing
t_token	*lexer(const char *input);
t_token	*tokenizing(const char *input);

// Token
char	*handle_word(const char **input, bool *in_double_quotes);
char	*get_quoted_word(const char **input, bool *in_dquote);
char	*get_unquoted_word(const char **input);
bool	handle_operator(t_token **token_list, const char **input);
bool	add_operator(t_token **token_list, const char **input, t_type op);
t_token	*init_token(t_token *head, char *str, t_type op, bool in_dquotes);
bool	add_token(t_token **head, char *str, t_type op, bool dquotes);

// Synthax utils
t_type	is_operator(const char *input);
bool	is_symbol(char c);
bool	is_parenthesis(char c);
bool	is_forbidden_char(char c);

//Error handling
bool	check_unclosed_quotes(const char *input);
bool	check_unclosed_parentheses(const char *input);
void	free_all(t_token *token);

#endif