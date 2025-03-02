/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_redirect.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:30:11 by raphalme          #+#    #+#             */
/*   Updated: 2025/03/02 16:15:55 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

bool	valid_type_redirect_in(t_token *cur)
{
	if (cur->type == REDIRECT_IN)
	{
		if (!(cur->prev->type == WORD && cur->next->type == WORD))
			return (false);
		if (!(cur->prev->type == HEREDOC || cur->prev->type == APPEND
				|| cur->prev->type == REDIRECT_IN
				|| cur->prev->type == REDIRECT_OUT)
				|| !(cur->next->type == HEREDOC || cur->next->type == APPEND
				|| cur->next->type == REDIRECT_IN
				|| cur->next->type == REDIRECT_OUT))
			return (false);
		if (!(cur->prev->type == PIPE || cur->next->type == PIPE))
			return (false);
		if(!(cur->prev->type == AND || cur->next->type == OR))
			return (false);
		if (!(cur->prev->type == O_PARENTHESIS 
		|| cur->next->type == C_PARENTHESIS))
			return (false);
	}
	return (true);
}

bool	t_tokenvalid_type_redirect_out(t_token *cur)
{
	if (cur->type == REDIRECT_OUT)
	{

	}
	return (true);
}
