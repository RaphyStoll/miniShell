/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/20 10:19:00 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

/**
 * @brief Validates the token list before building the AST.
 *
 * Checks general structure, redirection exceptions, and token placement.
 *
 * @param tokens Token list to validate.
 * @return true if valid, false otherwise.
 */

 //? handle_redirection_exceptions return false si cela marche
 //? pour eviter de continuer sur la suite de l'execution
bool	init_parsing(t_token *tokens)
{
	if (!valid_content(tokens))
		return (false);
	if ((handle_redirection_exceptions(tokens)))
		return (false);
			return (false);
	if (!if_valide_token_prev(tokens))
		return (false);
	if (!if_valide_token_next(tokens))
		return (false);
	return (true);
}
