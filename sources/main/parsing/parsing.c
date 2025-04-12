/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/12 19:36:34 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

// Fonction d'initialisation du parsing (à implémenter)

// il faut peut etre mettre return 1 au lieu de 0, car le main est a l envers ?

bool	init_parsing(t_token *tokens)
{
	if (!valid_content(tokens))
		return (false);
	if ((handle_redirection_exceptions(tokens)))
		return (true);
	if (!if_valide_token_prev(tokens))
		return (false);
	if (!if_valide_token_next(tokens))
		return (false);
	return (true);
}
