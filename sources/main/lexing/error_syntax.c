/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:35:59 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/13 15:55:35 by Charlye          ###   ########.fr       */
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
		return (ft_exit_error(NULL, UNCLOSED_QUOTE, error_token));
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
				return (ft_exit_error(NULL, UNCLOSED_PARENTHESIS, ")"));
			count--;
		}
		input++;
	}
	if (count > 0)
		return (ft_exit_error(NULL, UNCLOSED_PARENTHESIS, "("));
	return (true);
}

void	free_all(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->str);
		free(token);
		token = tmp;
	}
}

bool	ft_exit_error(t_token *tokens, t_error code, char *error_token)
{
	if (!error_token)
		error_token = "newline";
	if (code == UNCLOSED_QUOTE)
		printf(
			"Synthax error : unexpected EOF while looking for matching `%s'\n",
			error_token);
	else if (code == UNCLOSED_PARENTHESIS)
		printf("Syntax error: unexpected '%s'\n", error_token);
	else if (code == MEMORY_ERROR)
		printf("%s allocation error\n", error_token);
	else
		printf("Unknown error\n");
	if (tokens)
		free_all(tokens);
	return (false);
}
