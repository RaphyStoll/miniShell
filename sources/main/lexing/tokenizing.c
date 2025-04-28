/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/04/28 18:20:32 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"
#include "quote_type.h"
#include "expand.h"

/**
 * @brief Adds a new token to the end of the token list.
 *
 * @param head Pointer to the token list head.
 * @param str String to store in the token.
 * @param op Token type (e.g., WORD, PIPE, etc.).
 * @param quote_type Quote type associated with the token.
 * @return true on success, exits on memory allocation failure.
 */
bool	add_token(t_shell *shell, char *str, t_type op, t_quote quote_type)
{
	t_token	*new_token;
	t_token	*token;

	new_token = init_token(shell, str, op, quote_type);
	if (!new_token)
	{
		free(new_token);
		ft_exit_error(shell, MEMORY_ERROR, "memory");
	}
	if (!shell->tokens)
	{
		shell->tokens = new_token;
		return (true);
	}
	token = shell->tokens;
	while (token->next)
		token = token->next;
	token->next = new_token;
	new_token->prev = token;
	return (true);
}

char	*get_next_segment(const char **input, t_shell *shell, t_quote *quote)
{
	char	*seg;
	char	*expanded;
	t_quote	seg_quote;

	seg_quote = QUOTE_NONE;
	seg = get_quoted_word(input, &seg_quote);
	if (!seg)
		seg = get_unquoted_word(input);
	if (!seg || (seg_quote == QUOTE_NONE && !*seg))
		return (free(seg), NULL);
	if (seg_quote != QUOTE_SINGLE)
	{
		expanded = expand_one_arg(seg, shell);
		free(seg);
		if (!expanded)
			return (NULL);
		seg = expanded;
	}
	if (seg_quote == QUOTE_DOUBLE)
		*quote = QUOTE_DOUBLE;
	else if (seg_quote == QUOTE_SINGLE && *quote == QUOTE_NONE)
		*quote = QUOTE_SINGLE;
	return (seg);
}

/**
 * @brief Handles parsing a full word, combining quoted and unquoted segments.
 *
 * @param input Pointer to the input string.
 * @param quote_type Pointer to store the global quote type detected.
 * @return Newly allocated full word or NULL on failure.
 */
char	*handle_word(t_shell *shell, const char **input, t_quote *quote_type)
{
	char	*word;
	char	*seg;

	word = NULL;
	*quote_type = QUOTE_NONE;
	seg = get_next_segment(input, shell, quote_type);
	while (seg)
	{
		word = append_segment(word, seg);
		free(seg);
		if (!word)
			return (NULL);
		seg = get_next_segment(input, shell, quote_type);
	}
	return (word);
}
/**
 * @brief Handles parsing an operator or parenthesis from the input.
 *
 * @param token_list Pointer to the token list head.
 * @param input Pointer to the input string.
 * @return true if an operator was found and added, false otherwise.
 */

bool	handle_operator(t_shell *shell, const char **input)
{
	t_type	op;

	op = is_operator(*input);
	if (op != WORD)
		return (add_operator(shell, input, op));
	if (is_parenthesis(**input))
	{
		if (**input == '(')
			op = O_PARENTHESIS;
		else
			op = C_PARENTHESIS;
		return (add_operator(shell, input, op));
	}
	return (false);
}

/**
 * @brief Converts the input line into a list of tokens.
 *
 * @param input Input string to tokenize.
 * @return Head of the token list or NULL on error.
 */
t_token	*tokenizing(t_shell *shell, const char *input)
{
	t_quote			quote_type;
	char			*word;

	shell->tokens = NULL;
	while (*input)
	{
		if (*input == ' ')
		{
			input++;
			continue ;
		}
		if (handle_operator(shell, &input))
			continue ;
		if (is_forbidden_char(*input))
			return (ft_exit_error(shell, SYNTAX_ERROR, (char *)input));
		word = handle_word(shell, &input, &quote_type);
		if (!word)
			return (ft_exit_error(shell, MEMORY_ERROR, "word"));
		add_token(shell, word, WORD, quote_type);
		free(word);
	}
	return (shell->tokens);
}
