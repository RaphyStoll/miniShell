/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:30:11 by raphalme          #+#    #+#             */
/*   Updated: 2025/03/25 21:58:03 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"

bool	valid_type_redirect_in_prev(t_token *cur)
{
	if (cur->type == REDIRECT_IN)
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
		{
			printf("DEBUG : prev est NULL\n");
			return (false);
		}
		printf("DEBUG: prev = \"%s\" (Type: %d)\n", cur->prev->str, cur->prev->type);
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
		if(cur->prev->type == AND || cur->next->type == OR)
			return (false);
		if (cur->prev->type == O_PARENTHESIS 
		|| cur->next->type == C_PARENTHESIS)
			return (false);
		printf(MAGENTA BOLD"REDIRECT OUT is valid\n"NC);
	}
	return (true);
}
