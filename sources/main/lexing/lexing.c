/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/20 15:46:57 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

t_token	*lexer(const char *input)
{
	t_token	*token_list;

	if (!check_unclosed_quotes(input) || !check_unclosed_parentheses(input))
		return (NULL);
	token_list = tokenizing(input);
	if (!token_list)
	{
		printf("DEBUG: Lexer renvoie NULL\n");
		ft_exit_error2(token_list, MEMORY_ERROR, "token list");
	}
	return (token_list);
}
