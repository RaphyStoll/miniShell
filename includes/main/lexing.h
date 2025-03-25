/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/25 11:49:58 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "error_code.h"
# include "utils.h"
# include "../../lib/libft/header/libft.h"

// Enum for token type
typedef enum e_type
{
	WORD,			// arg or cmd 0
	PIPE,			// | 1
	REDIRECT_IN,	// < 2
	REDIRECT_OUT,	// > 3
	HEREDOC,		// << 4
	APPEND,			// >> 5
	AND,			// && 6
	OR,				// || 7
	O_PARENTHESIS,	// ( 8
	C_PARENTHESIS,	// ) 9
	INVALID_TOKEN
}	t_type;

// Token structure
typedef struct s_token
{
	char			*str;
	t_type			type;
	bool			in_double_quotes;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;


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