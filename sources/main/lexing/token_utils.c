/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:10:56 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/26 14:53:08 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"

/**
 * @brief Creates a new token node.
 *
 * @param head Current token list head.
 * @param str String to store in the token.
 * @param op Token type (e.g., WORD, PIPE, etc.).
 * @param quote_type Quote type associated with the token.
 * @return Pointer to the new token or exits on memory allocation failure.
 */
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

/**
 * @brief Adds a new token to the end of the token list.
 *
 * @param head Pointer to the token list head.
 * @param str String to store in the token.
 * @param op Token type (e.g., WORD, PIPE, etc.).
 * @param quote_type Quote type associated with the token.
 * @return true on success, exits on memory allocation failure.
 */
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

/**
 * @brief Adds an operator token to the token list based on the current input.
 *
 * @param token_list Pointer to the token list head.
 * @param input Pointer to the input string.
 * @param op Operator type to add.
 * @return true on success, false on memory allocation failure.
 */
bool	add_operator(t_token **token_list, const char **input, t_type op)
{
	char	*operator;

	if (op == HEREDOC || op == APPEND || op == AND || op == OR)
	{
		operator = ft_strndup(*input, 2);
		if (!operator)
			return (free_all(*token_list), free(input), false);
		*input += 2;
	}
	else
	{
		operator = ft_strndup(*input, 1);
		if (!operator)
			return (free_all(*token_list), free(input), false);
		*input += 1;
	}
	if (!operator)
		ft_exit_error(*token_list, MEMORY_ERROR, "memory");
	if (!(add_token(token_list, operator, op, false)))
	{
		free(operator);
		ft_exit_error(*token_list, MEMORY_ERROR, "token");
	}
	free (operator);
	return (true);
}

/**
 * @brief Handles parsing an operator or parenthesis from the input.
 *
 * @param token_list Pointer to the token list head.
 * @param input Pointer to the input string.
 * @return true if an operator was found and added, false otherwise.
 */
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
