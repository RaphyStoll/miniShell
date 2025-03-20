/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:45 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/20 14:38:06 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"
#include "../../../includes/main/ast.h"

void free_all(t_token *token)
{
	(void)token;
	return;
}

// Fonction pour libérer la liste de tokens
void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}


