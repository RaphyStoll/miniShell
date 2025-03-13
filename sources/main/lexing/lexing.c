/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/13 12:38:50 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

// Main function that processes inputs into tokens

bool	is_parenthesis(char c)
{
	return (c == '(' || c == ')');
}


int	is_symbol(char c)
{
	if (c == '(' || c == ')' || c == '<' || c == '>' || c == '&' || c == '|')
		return (1);
	return (0);
}

t_type	is_operator(const char *input)
{
	if (!ft_strncmp(input, ">>", 2))
		return (APPEND);
	if (!ft_strncmp(input, "<<", 2))
		return (HEREDOC);
	if (!ft_strncmp(input, "&&", 2))
		return (AND);
	if (!ft_strncmp(input, "||", 2))
		return (OR);
	if (*input == '|')
		return (PIPE);
	if (*input == '<')
		return (REDIRECT_IN);
	if (*input == '>')
		return (REDIRECT_OUT);
	return (WORD);
}

t_token	*lexer(const char *input)
{
	t_token	*token_list;

	check_unclosed_quotes(input);
	check_unclosed_parentheses(input);
	token_list = tokenizing(input);
	return (token_list);
}
