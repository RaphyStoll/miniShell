/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:20:23 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/20 23:10:14 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "minishell.h"

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

void	print_syntax_error(char *token)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("`", STDERR_FILENO);
}