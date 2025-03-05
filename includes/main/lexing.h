/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/04 14:15:14 by Charlye          ###   ########.fr       */
=======
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/02 15:27:45 by raphalme         ###   ########.fr       */
>>>>>>> parsing
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include <stdlib.h>
# include <stdio.h>
<<<<<<< HEAD
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
}	t_type;

=======

// Enum for token type
typedef enum e_token_type
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
}	t_token_type;

>>>>>>> parsing
// Token structure
typedef struct	s_token
{
	char			*str;
	t_type	type;
	struct s_token	*next;
}	t_token;

<<<<<<< HEAD
// Function prototypes lexer
t_token	lexer(const char *input);


// Token functions
t_token	*tokenizing(const char *input);
bool	handle_operator(t_token **token_list, const char **input);
bool	add_operator(t_token **token_list, const char **input, t_type op);
t_token	*tokenizing(const char *input);
t_type	is_operator(const char *input);
bool	is_parenthesis(char c);
=======
// Function prototypes
t_token	lexer(const char *input);
t_token	*tokenizing(const char *input);
>>>>>>> parsing
void	classify_token(t_token token);
void	free_token(t_token token);

// debug
<<<<<<< HEAD
void	print_token(t_token token);
=======
void	print_token(t_token *token);
>>>>>>> parsing

#endif