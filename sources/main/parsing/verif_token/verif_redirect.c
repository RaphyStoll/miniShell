/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:30:11 by raphalme          #+#    #+#             */
/*   Updated: 2025/05/05 15:08:18 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"

bool	valid_type_redirect_in_prev(t_token *cur)
{
	if (cur->type == REDIRECT_IN)
	{
		if (cur->prev == NULL)
			return (true);
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

bool	valid_type_redirect_in_next(t_token *cur)
{
	if (cur->type == REDIRECT_IN)
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

bool	valid_type_redirect_out_prev(t_token *cur)
{
	if (cur->type == REDIRECT_OUT)
	{
		if (cur->prev == NULL)
			return (true);
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

bool	valid_type_redirect_out_next(t_token *cur)
{
	if (cur->type == REDIRECT_OUT)
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

bool	valid_type_redirect_out(t_token *cur)
{
	if (cur->type == REDIRECT_OUT)
	{
		if (cur->prev == NULL)
			return (false);
		if (!(cur->prev->type == WORD && cur->next->type == WORD))
			return (false);
		if (cur->prev->type == HEREDOC || cur->prev->type == APPEND
			|| cur->prev->type == REDIRECT_IN
			|| cur->prev->type == REDIRECT_OUT
			|| cur->next->type == HEREDOC || cur->next->type == APPEND
			|| cur->next->type == REDIRECT_IN
			|| cur->next->type == REDIRECT_OUT)
			return (false);
		if (cur->prev->type == PIPE || cur->next->type == PIPE)
			return (false);
		if (cur->prev->type == AND || cur->next->type == OR)
			return (false);
		if (cur->prev->type == O_PARENTHESIS
			|| cur->next->type == C_PARENTHESIS)
			return (false);
	}
	return (true);
}
