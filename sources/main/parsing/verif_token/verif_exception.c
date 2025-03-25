/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:25:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/25 21:57:46 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"

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
