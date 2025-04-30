/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:10:56 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/30 08:02:50 by Charlye          ###   ########.fr       */
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
 * @brief Appends a segment to an existing word, handling memory reallocation.
 *
 * @param word Existing word to append to.
 * @param seg Segment to append.
 * @return Newly allocated string or NULL on failure.
 */
char	*append_segment(char *word, char *seg)
{
	char	*tmp;

	if (!word)
	{
		tmp = ft_strdup(seg);
		if (!tmp)
			return (NULL);
	}
	else
	{
		tmp = ft_strjoin(word, seg);
		if (!tmp)
			return (free(word), NULL);
		free(word);
	}
	return (tmp);
}

/**
 * @brief Extracts a quoted word from the input, updating the quote type.
 *
 * @param input Pointer to the input string.
 * @param quote_type Pointer to store the detected quote type.
 * @return Newly allocated quoted word or NULL on failure.
 */
char	*get_quoted_word(const char **input, t_quote *quote_type)
{
	int			len;
	const char	*start;
	char		quote;
	char		*word;

	len = 0;
	if (!input || !*input || (**input != '"' && **input != '\''))
		return (NULL);
	quote = **input;
	if (quote == '"')
		*quote_type = QUOTE_DOUBLE;
	else
		*quote_type = QUOTE_SINGLE;
	(*input)++;
	start = *input;
	while ((*input)[len] && (*input)[len] != quote)
		len++;
	if (!(*input)[len])
		return (NULL);
	(*input) += len + 1;
	word = ft_strndup(start, len);
	if (!word)
		return (NULL);
	return (word);
}

/**
 * @brief Extracts an unquoted word from the input.
 *
 * @param input Pointer to the input string.
 * @return Newly allocated unquoted word or NULL on failure.
 */
char	*get_unquoted_word(const char **input)
{
	int			len;
	const char	*start;
	char		*word;

	if (!input || !*input)
		return (NULL);
	len = 0;
	start = *input;
	while ((*input)[len]
		&& (*input)[len] != ' '
		&& (*input)[len] != '\t'
		&& !is_symbol((*input)[len])
		&& !is_quote((*input)[len]))
		len++;
	word = ft_strndup(start, len);
	if (!word)
		return (NULL);
	*input += len;
	return (word);
}
