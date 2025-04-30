/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 17:15:12 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/30 17:15:17 by Charlye          ###   ########.fr       */
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
bool	init_parsing(t_shell *shell, t_token *tokens, int *flag)
{
	if (!handle_redir_exceptions(shell, tokens, flag))
		return (SUCCESS);
	if (*flag == 0)
	{
		if (!valid_content(tokens))
			return (shell->last_exit_status = 2, false);
		if (!if_valide_token_prev(tokens))
			return (shell->last_exit_status = 2, false);
		if (!if_valide_token_next(tokens))
			return (shell->last_exit_status = 2, false);
	}
	return (true);
}
