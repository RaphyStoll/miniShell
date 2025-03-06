/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/06 16:36:42 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

// Enum for token type
typedef enum e_type
{
	WORD,			// arg or cmd
	PIPE,			// |	
	REDIRECT_IN,	// <
	REDIRECT_OUT,	// >
	HEREDOC,		// <<
	APPEND,			// >>
	AND,			// &&
	OR,				// ||
	O_PARENTHESIS,	// (
	C_PARENTHESIS,	// )
	INVALID_TOKEN
}	t_type;

// Token structure
typedef struct	s_token
{
	char			*str;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	t_token	*lexer;
	char	*synthax_error;
}	t_lexer;

// faire une strucutre qui regroupe toutes les variables que jutilise, a voir si jinsere dans s_lexer



// Function prototypes lexer
t_token	lexer(const char *input);


// Token functions
t_token	*tokenizing(const char *input);
bool	handle_operator(t_token **token_list, const char **input);
bool	add_operator(t_token **token_list, const char **input, t_type op);
t_token	*tokenizing(const char *input);
t_type	is_operator(const char *input);
bool	is_parenthesis(char c);
void	classify_token(t_token token);
void	free_token(t_token token);

// debug
void	print_token(t_token token);

#endif