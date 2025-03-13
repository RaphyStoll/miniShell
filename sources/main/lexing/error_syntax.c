/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:35:59 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/13 12:41:14 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

bool	check_unclosed_quotes(const char *input)
{
	char	quote;
	char	error_token[2];

	while (*input)
	{
		if (*input == '"' || *input == '\'')
		{
			quote = *input;
			error_token[0] = quote;
			error_token[1] = '\0';
			input++;
			while (*input && *input != quote)
				input++;
			if (!*input)
				ft_exit_error(NULL, UNCLOSED_QUOTE, error_token);
		}
		input++;
	}
	return (true);
}

bool	check_unclosed_parentheses(char *input)
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
				ft_exit_error(NULL, UNCLOSED_PARENTHESIS, ")");
			count--;
		}
		input++;
	}
	if (count > 0)
		ft_exit_error(NULL, UNCLOSED_PARENTHESIS, "(");
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

void	ft_exit_error(t_token *tokens, t_error code, char **error_token)
{
	if (!error_token)
		error_token = "newline";
	if (code == UNCLOSED_QUOTE)
		printf(stderr,
			"Synthax error : unexpected EOF while looking for matching `%s'\n",
			error_token);
	if (code == UNCLOSED_PARENTHESIS)
		printf(stderr, "Syntax error: unexpected '%s'\n" NC, error_token);
	if (code == MEMORY_ERROR)
		printf(stderr, "Memory allocation error\n");
	else
		printf(stderr, "Unknown error\n");
	if (tokens)
		free_all(tokens);
	exit(code);
}
