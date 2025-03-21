/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:19:25 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/20 19:30:25 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

bool	valid_type_and_prev(t_token *cur)
{
	if (cur->type == AND)
	{
		if (cur->prev == NULL)
			return (false);
		if (!(cur->prev->type == WORD))
			return (false);
		if (cur->prev->type == AND || cur->prev->type == OR)
			return (false);
		if (cur->prev->type == HEREDOC || cur->prev->type == APPEND)
			return (false);
		if (cur->prev->type == REDIRECT_IN || cur->prev->type == REDIRECT_OUT)
			return (false);
		if (cur->prev->type == PIPE)
			return (false);
	}
	return (true);
}

bool	valid_type_and_next(t_token *cur)
{
	if (cur->type == AND)
	{
		if (cur->next == NULL)
			return (false);
		if (!(cur->next->type == WORD))
			return (false);
		if (cur->next->type == AND || cur->next->type == OR)
			return (false);
		if (cur->next->type == HEREDOC || cur->next->type == APPEND)
			return (false);
		if (cur->next->type == REDIRECT_IN || cur->next->type == REDIRECT_OUT)
			return (false);
		if (cur->next->type == PIPE)
			return (false);
	}
	return (true);
}

bool	valid_type_or_prev(t_token *cur)
{
	if (cur->type == OR)
	{
		if (cur->prev == NULL)
			return (false);
		if (!(cur->prev->type == WORD || cur->prev->type == C_PARENTHESIS))
			return (false);
		if (cur->prev->type == AND || cur->prev->type == OR)
			return (false);
		if (cur->prev->type == HEREDOC || cur->prev->type == APPEND)
			return (false);
		if (cur->prev->type == REDIRECT_IN || cur->prev->type == REDIRECT_OUT)
			return (false);
		if (cur->prev->type == PIPE)
			return (false);
	}
	return (true);
}

bool	valid_type_or_next(t_token *cur)
{
	if (cur->type == OR)
	{
		if (cur->next == NULL)
			return (false);
		if (!(cur->next->type == WORD || cur->next->type == O_PARENTHESIS))
			return (false);
		if (cur->next->type == AND || cur->next->type == OR)
			return (false);
		if (cur->next->type == HEREDOC || cur->next->type == APPEND)
			return (false);
		if (cur->next->type == REDIRECT_IN || cur->next->type == REDIRECT_OUT)
			return (false);
		if (cur->next->type == PIPE)
			return (false);
	}
	return (true);
}
