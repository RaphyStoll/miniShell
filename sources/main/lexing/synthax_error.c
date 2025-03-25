/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:35:59 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/25 10:32:40 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

bool	check_unclosed_quotes(const char *input)
{
	char	quote;
	char	error_token[2];

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
	{
		ft_exit_error(NULL, UNCLOSED_QUOTE, error_token);
		return (false);
	}
	return (true);
}

bool	check_unclosed_parentheses(const char *input)
{
	int	count;

	count = 0;
	while (*input)
	{
		if (*input == '(')
			count++;
		else if (*input == ')')
		{
			if (count == 0)
			{
				ft_exit_error(NULL, UNCLOSED_PARENTHESIS, ")");
				return (false);
			}
			count--;
		}
		input++;
	}
	if (count > 0)
	{
		ft_exit_error(NULL, UNCLOSED_PARENTHESIS, "(");
		return (false);
	}
	return (true);
}
