/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/04/26 16:13:58 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_struct.h"	
#include "lexing.h"

/**
 * @brief Performs lexical analysis, creating a list of tokens.
 *
 * @param input Input string to tokenize.
 * @return Head of the token list, or NULL on error.
 */
t_token	*lexer(const char *input, t_shell *shell)
{
	t_token	*token_list;

	if (!check_unclosed_quotes(input) || !check_unclosed_parentheses(input))
		return (NULL);
	token_list = tokenizing(input, shell);
	if (!token_list)
		return (NULL);
	return (token_list);
}
