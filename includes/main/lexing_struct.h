/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_struct.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:48:07 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/27 11:25:12 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXING_STRUCT_H
# define LEXING_STRUCT_H

# include <stdbool.h>

// Enum for token type
/**
 * @brief enum pour le type de token
 */
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

/**
 * @brief strut de liste chainer pour les token
 * @param str contient la string du noeu de token
 * @param type enum pour definir le type du noeu de token
 * @param int_double_quotes flag si c'est en double quotes
 * @param next pointe vers le noeu suivant
 * @param prev pointe vers le noeu precedent
 */
typedef struct s_token
{
	char			*str;
	t_type			type;
	bool			in_double_quotes;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif