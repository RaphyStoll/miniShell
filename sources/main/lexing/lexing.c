/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/17 18:56:38 by Charlye          ###   ########.fr       */
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
		ft_exit_error(token_list, MEMORY_ERROR, "token list");
	return (token_list);
}
