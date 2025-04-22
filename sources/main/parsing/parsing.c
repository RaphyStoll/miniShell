/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/21 10:58:53 by raphaelferr      ###   ########.fr       */
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
	if (!handle_redirection_exceptions(tokens, flag))
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
