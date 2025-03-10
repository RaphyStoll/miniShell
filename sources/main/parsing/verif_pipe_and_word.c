/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_pipe_and_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:17:38 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/10 17:51:08 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

/* 
verifie si pipe est :
 - au debut ou a la fin de la liste
 - entourer de word
 - suivi ou preceder d'un autre pipe
*/

bool	valid_type_pipe(t_token *cur)
{
	if (cur->type == PIPE)
	{
		if (cur->prev == NULL || cur->next == NULL)
			return (false);
		if (!(cur->prev->type == PIPE || cur->next->type == PIPE))
			return (false);
		if (!(cur->prev->type == WORD || cur->prev->type == C_PARENTHESIS)
			&& !(cur->next->type == WORD || cur->next->type == O_PARENTHESIS))
			return (false);
		if (cur->prev->type == REDIRECT_IN || cur->prev->type == REDIRECT_OUT
			|| cur->prev->type == HEREDOC || cur->prev->type == APPEND)
			return (false);
		if (cur->next->type == REDIRECT_IN || cur->next->type == REDIRECT_OUT
			|| cur->next->type == HEREDOC || cur->next->type == APPEND)
			return (false);
		if ((cur->prev->type == AND || cur->prev->type == OR)
			&& (cur->next->type == AND || cur->next->type == OR))
			return (false);
	}
	return (true);
}

/*
Pour chaque token de type WORD,
vérifiez qu'il est précédé et suivi de tokens appropriés (par exemple,
pas de WORD directement après un PIPE sans un autre WORD avant)
*/
bool	valid_type_word(t_token *current)
{
	(void)current;
	return (true);
}
