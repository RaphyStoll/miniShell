/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:25:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/20 20:02:59 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

bool	handle_redirection_exceptions(t_token *token_list)
{
	if (!token_list)
		return (true);
	if (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT ||
		token_list->type == HEREDOC || token_list->type == APPEND)
	{
		if (token_list->next == NULL || token_list->next->type != WORD)
		{
			printf(RED"Error: Redirection requires a file name\n"NC);
			return (false);
		}
		printf(YELLOW"Special case: Redirection at the beginning\n"NC);
		return (true);
	}
	return (false);
}
