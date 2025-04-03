/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:23:24 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/03 16:34:44 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bultin.h"
#include "error_code.h"
#include "bultin_struct.h"
#include "../../../lib/libft/header/libft.h"

/**
 * @brief sert a activer les options dans la structure
 * si nouvelle option necessaire
 * refaire un if (arg == 'x') puis passer l'option a true dans  la structure
 * 
 * @param arg uniquement le char de l'option a activer
 * @param options pointeur vers la structure d'option par defaut tous sont a 0
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
 * @brief sert a parser echo pour que builtin_echo sache ou commence le texte
 * et sert aussi a activer les differentes option de echo
 * 
 * @param args tableau d'argument que reçoit echo (ex "-n", "-e")
 * @param options pointeur vers la structure d'option par defaut tous sont a 0
 * @param i conteur pour que bultin_echo sache ou commence le texte
 */
static void	parse_echo(char **args, t_echo_opts *options, int *i)
{
	int		j;
	bool	valid;

	*i = 1;
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
 * @brief sert a set par defaut les variable de la structure (default = 0)
 * prevu pour acceuillir plusieurs options a l'avenir et garantir 25 lignes
 * dans builtin_echo
 * 
 * @param options pointeur vers la structure d'option
 */
static void	init_options(t_echo_opts *options)
{
	options->n = 0;
	return ;
}

/**
 * @brief Bult-in echo: affiche les arguments, gere l'optionn -n
 * mais est prevu pour etre modulaire et rapidement inclure d'autres options
 * Exemple: echo -n -n "Hello world!"
 * 
 * @param args tableau d'argument que resoit echo ex:["-n","-n","Hello world!"]
 * @return int qui est le code d'erreur/succes de bash
 */
int	bultin_echo(char **args)
{
	t_echo_opts	options;
	int			i;

	init_options(&options);
	parse_echo(args, &options, &i);
	if (!args[i])
	{
		errno = 22;
		perror("echo");
		return (GENERIC_ERROR);
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