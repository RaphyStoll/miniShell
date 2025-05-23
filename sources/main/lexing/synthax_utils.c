/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:20:36 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/05 15:48:18 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"

bool	is_quote(char c)
{
	return (c == '"' || c == '\'');
}

bool	is_parenthesis(char c)
{
	return (c == '(' || c == ')');
}

bool	is_symbol(char c)
{
	return (c == '(' || c == ')' || c == '<' || c == '>'
		|| c == '&' || c == '|' || c == '\'' || c == ';');
}

bool	is_forbidden_char(char c)
{
	return (c == '&' || c == ';' || c == '\\');
}

t_type	is_operator(char *input)
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
