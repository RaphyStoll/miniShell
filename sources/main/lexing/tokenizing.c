/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/04/12 19:04:31 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"
#include "quote_type.h"

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

char	*get_unquoted_word(const char **input)
{
	int			len;
	const char	*start;
	char		*word;

	len = 0;
	start = *input;
	while ((*input)[len] && (*input)[len] != ' ' && !is_symbol((*input)[len]))
		len++;
	word = ft_strndup(start, len);
	*input += len;
	return (word);
}

char	*handle_word(const char **input, t_quote *quote_type)
{
	char	*quoted;
	char	*unquoted;
	char	*word;

	*quote_type = QUOTE_NONE;
	quoted = get_quoted_word(input, quote_type);
	unquoted = get_unquoted_word(input);
	if (quoted || unquoted)
	{
		if (!quoted)
			return (unquoted);
		if (!unquoted)
			return (quoted);
		word = ft_strjoin(quoted, unquoted);
		free(quoted);
		free(unquoted);
		return (word);
	}
	return (NULL);
}

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
