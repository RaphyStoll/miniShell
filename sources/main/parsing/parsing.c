/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2025/04/28 18:17:22 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"
#include "minishell.h"

/**
 * @brief Validates the token list before building the AST.
 *
 * Checks general structure, redirection exceptions, and token placement.
 *
 * @param tokens Token list to validate.
 * @return true if valid, false otherwise.
 */
bool	init_parsing(t_shell *shell, int *flag)
{
	t_token	*tokens;

	tokens = shell->tokens;
	if (!handle_redirection_exceptions(tokens, flag))
		return (SUCCESS);
	if (*flag == 0)
	{
		if (!valid_content(tokens))
			return (shell->last_exit_status = 2, false);
		if (!if_valide_token_prev(tokens))
			return (false);
		if (!if_valide_token_next(tokens))
			return (false);
	}
	return (true);
}
