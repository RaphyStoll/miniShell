/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/20 14:32:30 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include "../../includes/main/error_code.h"
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
bool	add_token(t_token **token_list, char *str, t_type op, bool dquotes);

// Synthax utils
t_type	is_operator(const char *input);
bool	is_symbol(char c);
bool	is_parenthesis(char c);

//Error handling
bool	check_unclosed_quotes(const char *input);
bool	check_unclosed_parentheses(const char *input);
void	ft_exit_error2(t_token *tokens, t_error code, char *error_token);
void	print_error_message(t_error code, char *error_token);
void	free_all2(t_token *token);

#endif