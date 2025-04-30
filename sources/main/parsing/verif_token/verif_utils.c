/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:10:28 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/30 17:10:30 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing_struct.h"
#include <stdlib.h>

bool	is_simple_redirection(t_token *token)
{
	if (token->prev != NULL)
		return (false);
	if (token->type != REDIRECT_IN
		&& token->type != REDIRECT_OUT
		&& token->type != APPEND
		&& token->type != HEREDOC)
		return (false);
	if (!token->next || token->next->type != WORD)
		return (false);
	if (token->next->next != NULL)
		return (false);
	return (true);
}
