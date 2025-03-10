/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:25:29 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/06 13:16:13 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_H
# define LEXING_H

# include <stdlib.h>
# include <stdio.h>

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

// Token structure
typedef struct	s_token
{
	char			*str;
	t_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

// Function prototypes
t_token	lexer(const char *input);
t_token	*tokenizing(const char *input);
void	classify_token(t_token token);
void	free_token(t_token token);

// debug
void	print_token(t_token token);

#endif