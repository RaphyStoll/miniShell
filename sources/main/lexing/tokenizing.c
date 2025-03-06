/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/06 17:22:27 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

bool	add_token(t_token **token_list, char *str, t_type op)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (false);
	new_token->str = strdup(str);
	if (!new_token->str)
	{
		free(new_token);
		return (false);
	}
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
		if (handle_operator(&token_list, &input))
			continue ;
		add_token(&token_list, handle_word(&input), 0);
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

char	*handle_word(const char **input)
{
	char	*word;
	int		len;

	len = 0;
	while ((*input[len] && *input[len] != ' ') && is_symbol(*input[len]) != 0)
		len++;
	word = ft_strndup(*input, len);
	*input += len;
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
