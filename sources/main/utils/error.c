/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 21:20:23 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/01 12:20:47 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"


// void	ft_exit_error(t_token *token, char *message, t_error error_code)
// {
// 	free_all(token);
// 	nbr_error(error_code, message);
// 	exit(error_code);
// }

// void nbr_error(t_error error_code, char *message) {
// 	if (error_code == GENERIC_ERROR)
// 		printf(RED BOLD"Error : General\n"NC);
// 	else if (error_code == USAGE_ERROR)
// 		printf(RED BOLD"Error : Usage\n"NC);
// 	else if (error_code == MATH_ERROR)
// 		printf(RED BOLD"Error : Math\n"NC);
// 	else if (error_code == SPECIFIC_ERROR_42)
// 		printf(RED BOLD"Error : 42 is 42\n"NC);
// 	else if (error_code == PERMISSION_ERROR)
// 		printf(RED BOLD"Error : No permission\n"NC);
// 	else if (error_code == SYNTAX_ERROR)
// 		printf(RED BOLD"Error : Syntax\n"NC);
// 	else if (error_code == COMMAND_NOT_FOUND)
// 		printf(RED BOLD"Error : Command not found\n"NC);
// 	else if (error_code == WRAPPER_ERROR)
// 		printf(RED BOLD"Error : Wrapper\n"NC);
// 	else
// 		perror(RED BOLD"Error"NC);
// 	printf(YELLOW"%s\n"NC, message);
// 	return ;
// }

void	print_error_message(t_error_code code, char *error_token)
{
	if (!error_token)
		error_token = "newline";
	write (2, "minishell: ", 11);
	if (code == UNCLOSED_QUOTE)
	{
		write(2,
			"syntax error near unexpected EOF while looking for matching '",
			61);
		write(2, error_token, 1);
		write(2, "'\n", 2);
	}
	else if (code == UNCLOSED_PARENTHESIS || code == SYNTAX_ERROR)
	{
		write(2, "syntax error near unexpected token '", 30);
		write(2, error_token, 1);
		write(2, "'\n", 2);
	}
	else if (code == MEMORY_ERROR)
	{
		write(2, error_token, ft_strlen(error_token));
		write(2, " allocation error\n", 18);
	}
	else
		write(2, "unknown error\n", 25);
}

t_token	*ft_exit_error(t_token *tokens, t_error_code code, char *error_token)
{
	print_error_message(code, error_token);
	if (tokens)
		free_all(tokens);
	return (NULL);
}