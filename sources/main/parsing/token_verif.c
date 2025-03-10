/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:19:28 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/10 17:51:04 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

//$ lance plusieurs arbres pour faire toutes les verif de position des token
bool	if_valide_token(t_token *tokens)
{
	t_token *current;

	current = tokens;
	print_tokens(current);
	while (current != NULL)
	{
		if (valid_content(current))
			return (false);
		if (valid_type_pipe(current))
			return (false);
		if (valid_type_word(current))
			return (false);
		if (valid_type_redirect_in(current))
			return (false);
		if (valid_type_redirect_out(current))
			return (false);
		if (valid_type_heredoc(current))
			return (false);
		if (valid_type_append(current))
			return (false);
		if (valid_type_and(current))
			return (false);
		if (valid_type_or(current))
			return (false);
	}
	return (true);
}

/*
Verifie si: 
 - un token est NULL
 - le type est compris dans la liste des token gere
*/
bool	valid_content(t_token *current)
{
	if (current->str == NULL)
		return (false);
	else if (!(current->type >= WORD && current->type <= C_PARENTHESIS))
		return (false);
	printf(MAGENTA BOLD"content valid\n"NC);
	return (true);
}
