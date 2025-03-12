/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:19:28 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/12 16:43:07 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"


//? dans un if la norme dit que c'est 1 pour vrais et 0 pour false
//? if (bool)
//? 	1
//? 0
//$ lance plusieurs arbres pour faire toutes les verif de position des token
bool	if_valide_token_prev(t_token *current)
{
	while (current != NULL)
	{
		print_current_token(current);
		printf(CYAN"valid_content = true\n");
		if (!valid_type_pipe_prev(current))
		{
			printf(RED"valid_type_pipe prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_pipe prev = true\n");
		if (!valid_type_word_prev(current))
		{
			printf(RED"valid_type_word prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_word prev = true\n");
		if (!valid_type_redirect_in_prev(current))
		{
			printf(RED"valid_type_redirect_in prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_redirect_in prev = true\n");
		if (!valid_type_redirect_out_prev(current))
		{
			printf(RED"valid_type_redirect_out prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_redirect_out prev = true\n");
		if (!valid_type_heredoc_prev(current))
		{
			printf(RED"valid_type_heredoc prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_heredoc prev = true\n");
		if (!valid_type_append_prev(current))
		{
			printf(RED"valid_type_append prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_append prev = true\n");
		if (!valid_type_and_prev(current))
		{
			printf(RED"valid_type_and prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_and prev = true\n");
		if (!valid_type_or_prev(current))
		{
			printf(RED"valid_type_or prev = false\n");
			return (false);
		}
		printf(CYAN"valid_type_or prev = true\n");
		current = current->next;
	}
	printf(MAGENTA BOLD"end verif\n"NC);
	return (true);
}

bool	if_valide_token_next(t_token *current)
{
	while (current != NULL)
	{
		print_current_token(current);
		if (!valid_type_pipe_next(current))
		{
			printf(RED"valid_type_pipe next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_pipe next = true\n");
		if (!valid_type_word_next(current))
		{
			printf(RED"valid_type_word next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_word next = true\n");
		if (!valid_type_redirect_in_next(current))
		{
			printf(RED"valid_type_redirect_in next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_redirect_in next = true\n");
		if (!valid_type_redirect_out_next(current))
		{
			printf(RED"valid_type_redirect_out next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_redirect_out next = true\n");
		if (!valid_type_heredoc_next(current))
		{
			printf(RED"valid_type_heredoc next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_heredoc next = true\n");
		if (!valid_type_append_next(current))
		{
			printf(RED"valid_type_append next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_append next = true\n");
		if (!valid_type_and_next(current))
		{
			printf(RED"valid_type_and next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_and next = true\n");
		if (!valid_type_or_next(current))
		{
			printf(RED"valid_type_or next = false\n");
			return (false);
		}
		printf(CYAN"valid_type_or next = true\n");
		current = current->next;
	}
	printf(MAGENTA BOLD"end verif\n"NC);
	return (true);
}

/*
Verifie si: 
 - un token est NULL
 - le type est compris dans la liste des token gere
*/
bool	valid_content(t_token *current)
{
	printf(CYAN"content verif start\n"NC);
    
    // D'abord vérifier si le pointeur current est NULL
    if (current == NULL)
    {
        printf(RED"token is NULL\n"NC);
        return (false);
    }
    
    if (current->str == NULL)
    {
        printf(RED"token string is NULL\n"NC);
        return (false);
    }
    
    if (!(current->type >= WORD && current->type <= C_PARENTHESIS))
    {
        printf(RED"invalid token type: %d\n"NC, current->type);
        return (false);
    }
    
    printf(CYAN"content verif end\n"NC);
    return (true);
}
