/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:20:21 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/06 11:08:27 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bultin.h"
#include "error_code.h"
/**
 * @brief Displays the current working directory.
 * This builtin command prints the absolute pathname of the current working directory
 * to the standard output. If an error occurs while retrieving the directory, an error
 * message is printed to the standard error.
 * @return int Returns SUCCESS (1) on success or GENERIC_ERROR (0) on failure.
 */
int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (GENERIC_ERROR);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}

/*
int main ()
{
	if (!builtin_pwd())
		return 1;
	return 0;
}
*/