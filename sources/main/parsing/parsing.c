/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/12 22:17:41 by raphael          ###   ########.fr       */
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
