/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:19:25 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/05 13:26:50 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

bool	valid_type_and(t_token *cur)
{
	if (cur->type == AND)
	{
		if (cur->prev == NULL || cur->next == NULL)
			return (false);
		if (!(cur->prev->type == WORD && cur->next->type == WORD))
			return (false);
		if (cur->prev->type == AND || cur->next->type == AND
			|| cur->prev->type == OR || cur->next->type == OR)
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
	}
	return (true);
}

bool	valid_type_or(t_token *cur)
{
	if (cur->type == OR)
	{
		if (cur->prev == NULL || cur->next == NULL)
			return (false);
		if (!(cur->prev->type == WORD && cur->next->type == WORD))
			return (false);
		if (cur->prev->type == AND || cur->next->type == AND
			|| cur->prev->type == OR || cur->next->type == OR)
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
	}
	return (true);
}