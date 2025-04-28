/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 21:19:28 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/28 18:37:09 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "lexing_struct.h"
#include "error_code.h"
#include "utils.h"
#include "debbug.h"

bool	if_valide_token_prev(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current != NULL)
	{
		if (!valid_type_pipe_prev(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "|"), false);
		if (!valid_type_redirect_in_prev(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "<"), false);
		if (!valid_type_redirect_out_prev(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, ">"), false);
		if (!valid_type_heredoc_prev(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "<<"), false);
		if (!valid_type_append_prev(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, ">>"), false);
		if (!valid_type_and_prev(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "&&"), false);
		if (!valid_type_or_prev(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "||"), false);
		if (!valid_type_word_prev(current))
			return (false);
		current = current->next;
	}
	return (true);
}

bool	if_valide_token_next(t_shell *shell)
{
	t_token	*current;

	current = shell->tokens;
	while (current != NULL)
	{
		if (!valid_type_pipe_next(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "|"), false);
		if (!valid_type_redirect_in_next(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "<"), false);
		if (!valid_type_redirect_out_next(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, ">"), false);
		if (!valid_type_heredoc_next(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "<<"), false);
		if (!valid_type_append_next(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, ">>"), false);
		if (!valid_type_and_next(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "&&"), false);
		if (!valid_type_or_next(current))
			return (ft_exit_error(shell, SYNTAX_ERROR, "||"), false);
		if (!valid_type_word_next(current))
			return (false);
		current = current->next;
	}
	return (true);
}

bool	valid_content(t_token *current)
{
	if (current == NULL)
		return (false);
	if (current->str == NULL)
		return (false);
	if (!(current->type >= WORD && current->type <= C_PARENTHESIS))
		return (false);
	return (true);
}
