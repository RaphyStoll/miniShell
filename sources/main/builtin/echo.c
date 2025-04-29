/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:23:24 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/29 22:44:13 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "builtin_struct.h"
#include "error_code.h"
#include "builtin.h"
#include "debbug.h"

/**
 * @brief Activates an option in the structure.
 *
 * This function activates the corresponding option in the options structure
 * based on the given option character. To add additional options, include
 * a new condition such as "if (arg == 'x')" and set the corresponding
 * option to true.
 * 
 * @param arg The option character to activate.
 * @param options Pointer to the options structure where all
 * 				  options are initially false.
 * @return true 
 * @return false 
 */
static bool	check_args(char arg, t_echo_opts *options)
{
	if (arg == 'n')
		options->n = true;
	else
		return (false);
	return (true);
}

/**
 * @brief Parses the echo command arguments.
 * 
 * This function processes the array of arguments received by echo.
 * It determines the starting index for the text to be echoed and activates
 * the corresponding options in the options structure.
 *
 * @param args Array of arguments received by echo (e.g., "-n", "-e").
 * @param options Pointer to the options structure.
 * @param i Pointer to an integer that will be updated with the index
 * 			where the text begins.
 */
static void	parse_echo(char **args, t_echo_opts *options, int *i)
{
	int		j;
	bool	valid;

	*i = 1;
	if (!args[*i])
		return ;
	if (args[*i][0] == '-' && !args[*i][1])
		printf("-");
	while (args[*i] && args[*i][0] == '-')
	{
		j = 1;
		valid = true;
		while (args[*i][j])
		{
			if (!(check_args(args[*i][j], options)))
			{
				valid = false;
				break ;
			}
			j++;
		}
		if (!valid)
			break ;
		(*i)++;
	}
}

/**
 * @brief Initializes the echo options with default values.
 *
 * This function sets the default values for the echo options structure.
 * It currently initializes the -n option to false.
 *
 * @param options Pointer to the echo options structure.
 */
static void	init_options(t_echo_opts *options)
{
	options->n = 0;
	return ;
}

/**
 * @brief Built-in echo command: displays the arguments.
 *
 * This built-in command prints the provided arguments to the standard output.
 * It handles the -n option to suppress the trailing newline and
 * is designed to be modular, allowing for the easy inclusion
 * of additional options in the future.
 *
 * For example: echo -n -n "Hello world!".
 *
 * @param args Array of arguments received by echo
 * 				(e.g., {"-n", "-n", "Hello world!"}).
 * @return int SUCCESS on success or an appropriate error code on failure.
 */
int	builtin_echo(char **args)
{
	t_echo_opts	options;
	int			i;

	init_options(&options);
	parse_echo(args, &options, &i);
	if (!args[i])
	{
		if (!options.n)
			printf("\n");
		return (SUCCESS);
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!options.n)
		printf("\n");
	return (SUCCESS);
}

/*
int main ()
{
	char *args[] = {"echo", "-nnnnnnnnnnnnnnn", "Hello", "world", "!", NULL};
	return (bultin_echo(args));
}
*/