/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/04 14:15:35 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

bool	is_parenthesis(char c)
{
	return (c == '(' || c == ')');
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

// Split input into a list of raw tokens
t_token	*tokenizing(const char *input)
{
	t_token	*token_list;

	token_list = NULL;
	while (*input)
	{
		if (*input == ' ')
		{
			input++;
			continue ;
		}
		if (handle_operators(&token_list, &input))
			continue ;
		add_token(&token_list, handle_word(&input));
	}
	return (token_list);
}

bool	add_operator(t_token **token_list, const char **input, t_type op)
{
	if (!(add_token(token_list, ft_strdup(*input), op)))
		return (false);
	if (op == HEREDOC || op == APPEND || op == AND || op == OR)
		*input += 2;
	else
		*input += 1;
	return (true);
}

bool	handle_operator(t_token **token_list, const char **input)
{
	t_type	op;

	op = is_operator(*input);
	if (op != WORD)
		return (add_operator(token_list, input, op));
	if (is_parenthesis(**input))
	{
		if (**input == '(')
			op = O_PARENTHESIS;
		else
			op = C_PARENTHESIS;
		return (add_operator(token_list, input, op));
	}
	return (false);
}
