/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/04/26 15:18:58 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"
#include "quote_type.h"

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
	if (**input != '"' && **input != '\'')
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

	len = 0;
	start = *input;
	while ((*input)[len]
		&& (*input)[len] != ' '
		&& !is_symbol((*input)[len])
		&& !is_quote((*input)[len]))
		len++;
	word = ft_strndup(start, len);
	*input += len;
	return (word);
}

/**
 * @brief Handles parsing a full word, combining quoted and unquoted segments.
 *
 * @param input Pointer to the input string.
 * @param quote_type Pointer to store the global quote type detected.
 * @return Newly allocated full word or NULL on failure.
 */
char	*handle_word(const char **input, t_quote *quote_type)
{
	char	*word;
	char	*seg;
	t_quote	seg_quote;

	word = NULL;
	*quote_type = QUOTE_NONE;
	while (1)
	{
		seg_quote = QUOTE_NONE;
		seg = get_quoted_word(input, &seg_quote);
		if (!seg)
			seg = get_unquoted_word(input);
		if (!seg || (seg_quote == QUOTE_NONE && !*seg))
		{
			free(seg);
			break ;
		}
		if (seg_quote == QUOTE_DOUBLE)
			*quote_type = QUOTE_DOUBLE;
		word = append_segment(word, seg);
		free(seg);
		if (!word)
			return (NULL);
	}
	return (word);
}

/**
 * @brief Converts the input line into a list of tokens.
 *
 * @param input Input string to tokenize.
 * @return Head of the token list or NULL on error.
 */
t_token	*tokenizing(const char *input)
{
	t_token			*token_list;
	t_quote			quote_type;
	char			*word;

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
		if (is_forbidden_char(*input))
			return (ft_exit_error(token_list, SYNTAX_ERROR, (char *)input));
		word = handle_word(&input, &quote_type);
		if (!word)
			return (ft_exit_error(token_list, MEMORY_ERROR, "word"));
		add_token(&token_list, word, WORD, quote_type);
		free(word);
	}
	return (token_list);
}
