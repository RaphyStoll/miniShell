/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:10:56 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/01 12:34:26 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"

t_token	*init_token(t_token *head, char *str, t_type op, t_quote quote_type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		ft_exit_error(head, MEMORY_ERROR, "memory");
	new_token->str = strdup(str);
	if (!new_token->str)
	{
		free(new_token);
		ft_exit_error(head, MEMORY_ERROR, "memory");
	}
	new_token->type = op;
	new_token->quote_type = quote_type;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

bool	add_token(t_token **head, char *str, t_type op, t_quote quote_type)
{
	t_token	*new_token;
	t_token	*token;

	new_token = init_token(*head, str, op, quote_type);
	if (!new_token)
	{
		free(new_token);
		ft_exit_error(*head, MEMORY_ERROR, "memory");
	}
	if (!*head)
	{
		*head = new_token;
		return (true);
	}
	token = *head;
	while (token->next)
		token = token->next;
	token->next = new_token;
	new_token->prev = token;
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
	if (!(add_token(token_list, operator, op, false)))
	{
		free(operator);
		ft_exit_error(*token_list, MEMORY_ERROR, "token");
	}
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
