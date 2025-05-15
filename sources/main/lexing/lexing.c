/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:00 by chpasqui          #+#    #+#             */
/*   Updated: 2025/05/05 10:54:50 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_struct.h"	
#include "lexing.h"

t_token	*get_last_token(t_token *token_list)
{
	t_token	*t;

	t = token_list;
	while (t && t->next)
		t = t->next;
	return (t);
}

bool	handle_word_token(t_token **token, char **in, t_shell *sh, t_quote *q)
{
	char	*word;

	word = handle_word(in, q, sh);
	if (!word)
		return (false);
	add_token(token, word, WORD, *q);
	free(word);
	return (true);
}

t_token	*tokenizing(char *input, t_shell *shell)
{
	t_token	*token_list;
	t_quote	quote_type;
	bool	next_is_hd;

	token_list = NULL;
	next_is_hd = false;
	if (!input || !*input)
		return (NULL);
	while (*input)
	{
		skip_whitespace(&input);
		if (heredoc_delim(&token_list, &input, &next_is_hd, &quote_type))
			continue ;
		if (handle_operator(&token_list, &input))
		{
			next_is_hd = (get_last_token(token_list)->type == HEREDOC);
			continue ;
		}
		if (is_forbidden_char(*input))
			return (ft_exit_error(token_list, SYNTAX_ERROR, (char *)input));
		if (!handle_word_token(&token_list, &input, shell, &quote_type))
			return (ft_exit_error(token_list, MEMORY_ERROR, "word"));
	}
	return (token_list);
}

/**
 * @brief Performs lexical analysis, creating a list of tokens.
 *
 * @param input Input string to tokenize.
 * @return Head of the token list, or NULL on error.
 */
t_token	*lexer(char *input, t_shell *shell)
{
	t_token	*token_list;

	if (!check_unclosed_quotes(input) || !check_unclosed_parentheses(input))
	{
		shell->last_exit_status = 2;
		return (NULL);
	}
	token_list = tokenizing(input, shell);
	if (!token_list)
		return (NULL);
	return (token_list);
}
