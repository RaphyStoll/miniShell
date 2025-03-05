/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:19:28 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/03 21:19:29 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

bool	if_valide_token(t_token *tokens)
{
	t_token *current;

	current = tokens;
	while (current != NULL)
	{
		printf(YELLOW"Not NULL\n"NC);
		if (!valid_content(current)) //$ false si type_token = NULL ou type inconnu
			return (false);
		if (valid_type_pipe(current)) //$ arbre de verification des pipes
			return (false);
		if (valid_type_word(current)) //$ arbre de verif des WORd
			return (false);
	}
	return (true);
}

/*
Verifie si: 
 - un tokken est NULL
 - le type est compris dans la liste des tokken gere
*/
bool	valid_content(t_token *current)
{
	if (current->str == NULL)
		return (false);
	else if (!(current->type >= WORD && current->type <= C_PARENTHESIS))
		return (false);
	return (true);
}
