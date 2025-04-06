/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_pipe_and_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:17:38 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/06 10:52:36 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"

bool	valid_type_pipe_prev(t_token *cur)
{
	if (cur->type == PIPE)
	{
		if (cur->prev == NULL)
			return (false);
		if (cur->prev->type == PIPE)
			return (false);
		if (!(cur->prev->type == WORD || cur->prev->type == C_PARENTHESIS))
			return (false);
		if (cur->prev->type == REDIRECT_IN || cur->prev->type == REDIRECT_OUT)
			return (false);
		if (cur->prev->type == HEREDOC || cur->prev->type == APPEND)
			return (false);
		if (cur->prev->type == AND || cur->prev->type == OR)
			return (false);
	}
	return (true);
}

bool	valid_type_pipe_next(t_token *cur)
{
	if (cur->type == PIPE)
	{
		if (cur->next == NULL)
			return (false);
		if (cur->next->type == PIPE)
			return (false);
		if (!(cur->next->type == WORD || cur->next->type == O_PARENTHESIS))
			return (false);
		if (cur->next->type == REDIRECT_IN || cur->next->type == REDIRECT_OUT)
			return (false);
		if (cur->next->type == HEREDOC || cur->next->type == APPEND)
			return (false);
		if (cur->next->type == AND || cur->next->type == OR)
			return (false);
	}
	return (true);
}

bool	valid_type_word_prev(t_token *cur)
{
	if (cur->type == WORD)
	{
		if (cur->prev == NULL)
			return (true);
		if (cur->prev->type == C_PARENTHESIS)
				return (false);
	}
	return (true);
}

bool	valid_type_word_next(t_token *cur)
{
	if (cur->type == WORD)
	{
		if (cur->next == NULL)
			return (true);
		if (cur->next->type == O_PARENTHESIS)
			return (false);
	}
	return (true);
}
