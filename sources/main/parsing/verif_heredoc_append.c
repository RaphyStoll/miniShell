/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_heredoc_append.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 11:18:29 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/09 15:31:31 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

bool	valid_type_heredoc(t_token *cur)
{
	if (cur->type == HEREDOC)
	{
		if (cur->prev == NULL || cur->next == NULL)
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
		if (cur->prev->type == PIPE || cur->next->type == PIPE
			|| cur->prev->type == AND || cur->next->type == OR)
			return (false);
		if (cur->prev->type == O_PARENTHESIS
			|| cur->next->type == C_PARENTHESIS)
			return (false);
	}
	return (true);
}

bool	valid_type_append(t_token *cur)
{
	if (cur->type == APPEND)
	{
		if (cur->prev == NULL || cur->next == NULL)
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
		if (cur->prev->type == PIPE || cur->next->type == PIPE
			|| cur->prev->type == AND || cur->next->type == OR)
			return (false);
		if (cur->prev->type == O_PARENTHESIS
			|| cur->next->type == C_PARENTHESIS)
			return (false);
	}
	return (true);
}
