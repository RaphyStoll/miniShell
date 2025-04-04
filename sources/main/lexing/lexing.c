/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/25 20:49:06 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_struct.h"	
#include "lexing.h"

t_token	*lexer(const char *input)
{
	t_token	*token_list;

	if (!check_unclosed_quotes(input) || !check_unclosed_parentheses(input))
		return (NULL);
	token_list = tokenizing(input);
	if (!token_list)
		return (NULL);
	return (token_list);
}
