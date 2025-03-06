/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/06 14:16:48 by chpasqui         ###   ########.fr       */
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
t_token lexer(const char *input)
{

}