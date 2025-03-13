/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/13 16:10:41 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

bool	add_token(t_token **token_list, char *str, t_type op)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		ft_exit_error(*token_list, MEMORY_ERROR, "memory");
	new_token->str = strdup(str);
	if (!new_token->str)
		ft_exit_error(*token_list, MEMORY_ERROR, "memory");
	new_token->type = op;
	new_token->next = NULL;
	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		tmp = *token_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_token;
	}
	return (true);
}

bool	add_operator(t_token **token_list, const char **input, t_type op)
{
	char	*operator;

	if (op == HEREDOC || op == APPEND || op == AND || op == OR)
	{
		operator = ft_strndup(*input, 2);
		*input += 2;
	}
	else
	{
		operator = ft_strndup(*input, 1);
		*input += 1;
	}
	if (!operator)
		ft_exit_error(*token_list, MEMORY_ERROR, "memory");
	if (!(add_token(token_list, operator, op)))
	{
		free(operator);
		ft_exit_error(*token_list, MEMORY_ERROR, "token");
	}
	return (true);
}

char	*handle_word(const char **input)
{
	char	*word;
	char	quote;
	int		len;

	len = 0;
	if (**input == '"' || **input == '\'')
	{
		quote = **input;
		(*input)++;
		while ((*input)[len] && (*input)[len] != quote)
			len++;
		if (!(*input)[len])
			return (NULL);
		word = ft_strndup(*input, len);
		*input += len + 1;
	}
	else
	{
		while (((*input)[len] && (*input)[len] != ' ')
			&& !is_symbol((*input)[len]))
			len++;
		word = ft_strndup(*input, len);
		*input += len;
	}
	return (word);
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

// Split input into a list of raw tokens
t_token	*tokenizing(const char *input)
{
	t_token	*token_list;
	char	*word;

	token_list = NULL;
	while (*input)
	{
		if (*input == ' ')
		{
			input++;
			continue ;
		}
		if (handle_operator(&token_list, &input))
			continue ;
		word = handle_word(&input);
		if (!word)
			ft_exit_error(token_list, MEMORY_ERROR, "word");
		add_token(&token_list, word, 0);
	}
	return (token_list);
}
