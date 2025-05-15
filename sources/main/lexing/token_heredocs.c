/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:40:23 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/05 10:54:24 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
#include "lexing_struct.h"
#include "quote_type.h"
#include "expand.h"

bool	heredoc_delim(t_token **token, char **input, bool *next_hd, t_quote *q)
{
	char	*delim;

	if (!*next_hd)
		return (false);
	skip_whitespace(input);
	if (**input == '"' || **input == '\'')
		delim = get_quoted_word(input, q);
	else
	{
		*q = QUOTE_NONE;
		delim = get_unquoted_word(input);
	}
	if (!delim)
		return (ft_exit_error(*token, SYNTAX_ERROR, "here-doc delim"));
	add_token(token, delim, WORD, *q);
	free(delim);
	*next_hd = false;
	return (true);
}
