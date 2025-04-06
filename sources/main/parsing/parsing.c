/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/06 11:35:22 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

// Fonction d'initialisation du parsing (à implémenter)

// il faut peut etre mettre return 1 au lieu de 0, car le main est a l envers ?

bool	init_parsing(t_token *tokens)
{
	if (!valid_content(tokens))
		return (1);
	if ((handle_redirection_exceptions(tokens)))
		return (0);
	if (!if_valide_token_prev(tokens))
		return (1);
	if (!if_valide_token_next(tokens))
		return (1);
	return (0);
}
