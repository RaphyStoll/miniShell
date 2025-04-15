/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:20:23 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/14 13:34:44 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_error_message(t_error_code code, char *error_token)
{
	if (!error_token)
		error_token = "newline";
	write (2, "minishell: ", 11);
	if (code == UNCLOSED_QUOTE)
	{
		write(2,
			"syntax error near unexpected EOF while looking for matching\n",
			60);
		write(2, error_token, 1);
		write(2, "'\n", 2);
	}
	else if (code == UNCLOSED_PARENTHESIS || code == SYNTAX_ERROR)
	{
		write(2, "syntax error near unexpected token\n", 35);
		write(2, error_token, 1);
		write(2, "'\n", 2);
	}
	else if (code == MEMORY_ERROR)
	{
		write(2, error_token, ft_strlen(error_token));
		write(2, " allocation error\n", 17);
	}
	else
		write(2, "unknown error\n", 14);
}

t_token	*ft_exit_error(t_token *tokens, t_error_code code, char *error_token)
{
	print_error_message(code, error_token);
	if (tokens)
		free_all(tokens);
	return (NULL);
}
