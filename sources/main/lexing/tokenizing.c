/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/03/25 21:48:47 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"

char	*get_quoted_word(const char **input, bool *in_dquote)
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
		*in_dquote = true;
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

char	*handle_word(const char **input, bool *in_double_quotes)
{
	char	*quoted;
	char	*unquoted;
	char	*word;

	*in_double_quotes = false;
	quoted = get_quoted_word(input, in_double_quotes);
	unquoted = get_unquoted_word(input);
	if (quoted)
	{
		word = ft_strjoin(quoted, unquoted);
		free(quoted);
		free(unquoted);
		if (!word)
			return (NULL);
		return (word);
	}
	return (unquoted);
}

t_token	*tokenizing(const char *input)
{
	t_token	*token_list;
	char	*word;
	bool	dquote;

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
		word = handle_word(&input, &dquote);
		if (!word)
			return (ft_exit_error(token_list, MEMORY_ERROR, "word"));
		add_token(&token_list, word, WORD, dquote);
	}
	return (token_list);
}
