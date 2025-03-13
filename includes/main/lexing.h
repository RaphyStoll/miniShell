/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/13 16:07:59 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
#include "../../lib/libft/header/libft.h"
#include "../../lib/libft/header/libft_bonus.h"

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
typedef struct	s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_lexer
{
	t_token	*lexer;
	char	*synthax_error;
}	t_lexer;

// faire une strucutre qui regroupe toutes les variables que jutilise, a voir si jinsere dans s_lexer

typedef enum e_error
{
	UNCLOSED_QUOTE,
	UNCLOSED_PARENTHESIS,
	MEMORY_ERROR,
}	t_error;


// Function prototypes lexer
// Function prototypes
t_token	*lexer(const char *input);
t_token	*tokenizing(const char *input);
bool	handle_operator(t_token **token_list, const char **input);
bool	add_operator(t_token **token_list, const char **input, t_type op);
char	*handle_word(const char **input);
bool	add_token(t_token **token_list, char *str, t_type op);
t_type	is_operator(const char *input);
bool	is_symbol(char c);
bool	is_parenthesis(char c);
bool	check_unclosed_quotes(const char *input);
bool	check_unclosed_parentheses(const char *input);
bool	ft_exit_error(t_token *tokens, t_error code, char *error_token);
void	free_all(t_token *token);

// debug
void	print_token(t_token token);

#endif