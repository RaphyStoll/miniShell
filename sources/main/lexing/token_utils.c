/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:10:56 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/20 14:24:53 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

bool	add_token(t_token **token_list, char *str, t_type op, bool in_dquotes)
{
	t_token	*new_token;
	t_token	*tmp;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		ft_exit_error2(*token_list, MEMORY_ERROR, "memory");
	new_token->str = strdup(str);
	if (!new_token->str)
	{
		free(new_token);
		ft_exit_error2(*token_list, MEMORY_ERROR, "memory");
	}
	new_token->type = op;
	new_token->in_double_quotes = in_dquotes;
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
		ft_exit_error2(*token_list, MEMORY_ERROR, "memory");
	if (!(add_token(token_list, operator, op, false)))
	{
		free(operator);
		ft_exit_error2(*token_list, MEMORY_ERROR, "token");
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
