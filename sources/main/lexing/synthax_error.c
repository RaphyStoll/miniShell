/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:35:59 by chpasqui          #+#    #+#             */
/*   Updated: 2025/04/30 07:45:51 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"

/**
 * @brief Checks if there are any unclosed quotes in the input string.
 *
 * @param input Input string to check.
 * @return true if quotes are properly closed, false otherwise
 */
bool	check_unclosed_quotes(const char *input)
{
	char	quote;
	char	error_token[2];

	if (!input)
		return (false);
	quote = 0;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
		{
			if (quote == 0)
			{
				quote = *input;
				error_token[0] = quote;
				error_token[1] = '\0';
			}
			else if (quote == *input)
				quote = 0;
		}
		input++;
	}
	if (quote)
		return (ft_exit_error(NULL, UNCLOSED_QUOTE, error_token), false);
	return (true);
}

/**
 * @brief Checks if there are any unclosed or unmatched parentheses
 *
 * @param input Input string to check.
 * @return true if all parentheses are properly closed, false otherwise.
 */
bool	check_unclosed_parentheses(const char *input)
{
	int	count;

	if (!input)
		return (false);
	count = 0;
	while (*input)
	{
		if (*input == '(')
			count++;
		else if (*input == ')')
		{
			if (count == 0)
				return (ft_exit_error(NULL, UNCLOSED_PARENTHESIS, ")"), false);
			count--;
		}
		input++;
	}
	if (count > 0)
		return (ft_exit_error(NULL, UNCLOSED_PARENTHESIS, "("), false);
	return (true);
}
