/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:35:59 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/20 16:21:46 by Charlye          ###   ########.fr       */
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
		ft_exit_error2(NULL, UNCLOSED_QUOTE, error_token);
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
				ft_exit_error2(NULL, UNCLOSED_PARENTHESIS, ")");
				return (false);
			}
			count--;
		}
		input++;
	}
	if (count > 0)
	{
		ft_exit_error2(NULL, UNCLOSED_PARENTHESIS, "(");
		return (false);
	}
	return (true);
}

void	print_error_message(t_error code, char *error_token)
{
	if (!error_token)
		error_token = "newline";
	write (2, "minishell: ", 11);
	if (code == UNCLOSED_QUOTE)
	{
		write(2,
			"syntax error near unexpected EOF while looking for matching '",
			61);
		write(2, error_token, 1);
		write(2, "'\n", 2);
	}
	else if (code == UNCLOSED_PARENTHESIS)
	{
		write(2, "syntax error near unexpected '", 30);
		write(2, error_token, 1);
		write(2, "'\n", 2);
	}
	else if (code == MEMORY_ERROR)
	{
		write(2, error_token, ft_strlen(error_token));
		write(2, "allocation error\n", 18);
	}
	else
		write(2, "unknown error\n", 25);
}

void	ft_exit_error2(t_token *tokens, t_error code, char *error_token)
{
	print_error_message(code, error_token);
	if (tokens)
		free_all2(tokens);
}
