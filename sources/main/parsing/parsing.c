/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/21 00:25:56 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Validates the token list before building the AST.
 *
 * Checks general structure, redirection exceptions, and token placement.
 *
 * @param tokens Token list to validate.
 * @return true if valid, false otherwise.
 */
bool	init_parsing(t_token *tokens, int *flag)
{
	//print_tokens(tokens);
		if (!handle_redirection_exceptions(tokens, flag))
			return (F_ADDFILESIGS_RETURN);
		if (flag == 0)
		{
			if (!valid_content(tokens))
				return (false);
			if (!if_valide_token_prev(tokens))
				return (false);
			if (!if_valide_token_next(tokens))
				return (false);
		}
	return (true);
}
