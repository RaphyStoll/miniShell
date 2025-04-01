/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:20:21 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/01 16:46:57 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bultin.h"
#include "error_code.h"

int	builtin_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("pwd"), GENERIC_ERROR);
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