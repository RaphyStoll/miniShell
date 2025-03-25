/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_heredoc_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:18:29 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/25 21:57:52 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"

bool	valid_type_heredoc_prev(t_token *cur)
{
	if (cur->type == HEREDOC)
	{
		if (cur->prev == NULL)
			return (false);
		if (!(cur->prev->type == WORD))
			return (false);
		if (cur->prev->type == HEREDOC || cur->prev->type == APPEND)
			return (false);
		if (cur->prev->type == REDIRECT_IN || cur->prev->type == REDIRECT_OUT)
			return (false);
		if (cur->prev->type == PIPE)
			return (false);
		if (cur->prev->type == AND)
			return (false);
		if (cur->prev->type == O_PARENTHESIS)
			return (false);
	}
	return (true);
}

bool	valid_type_heredoc_next(t_token *cur)
{
	if (cur->type == HEREDOC)
	{
		if (cur->next == NULL)
			return (false);
		if (!(cur->next->type == WORD))
			return (false);
		if (cur->next->type == HEREDOC || cur->next->type == APPEND)
			return (false);
		if (cur->next->type == REDIRECT_IN || cur->next->type == REDIRECT_OUT)
			return (false);
		if (cur->next->type == PIPE)
			return (false);
		if (cur->next->type == OR)
			return (false);
		if (cur->next->type == C_PARENTHESIS)
			return (false);
	}
	return (true);
}

bool	valid_type_append_prev(t_token *cur)
{
	if (cur->type == APPEND)
	{
		if (cur->prev == NULL)
			return (false);
		if (!(cur->prev->type == WORD))
			return (false);
		if (cur->prev->type == HEREDOC || cur->prev->type == APPEND)
			return (false);
		if (cur->prev->type == REDIRECT_IN || cur->prev->type == REDIRECT_OUT)
			return (false);
		if (cur->prev->type == PIPE)
			return (false);
		if (cur->prev->type == AND)
			return (false);
		if (cur->prev->type == O_PARENTHESIS)
			return (false);
	}
	return (true);
}

bool	valid_type_append_next(t_token *cur)
{
	if (cur->type == APPEND)
	{
		if (cur->next == NULL)
			return (false);
		if (!(cur->next->type == WORD))
			return (false);
		if (cur->next->type == HEREDOC || cur->next->type == APPEND)
			return (false);
		if (cur->next->type == REDIRECT_IN || cur->next->type == REDIRECT_OUT)
			return (false);
		if (cur->next->type == PIPE)
			return (false);
		if (cur->next->type == AND)
			return (false);
		if (cur->next->type == O_PARENTHESIS)
			return (false);
	}
	return (true);
}
