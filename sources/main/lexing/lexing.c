/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/04/28 18:23:19 by Charlye          ###   ########.fr       */
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
t_token	*lexer(t_shell *shell, const char *input)
{
	if (!check_unclosed_quotes(shell, input)
		|| !check_unclosed_parentheses(shell, input))
		return (NULL);
	shell->tokens = tokenizing(shell, input);
	if (!shell->tokens)
		return (NULL);
	return (shell->tokens);
}
