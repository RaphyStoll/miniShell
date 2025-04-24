/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:22:19 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/24 19:09:47 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "minishell.h"
#include "env_struct.h"
#include <unistd.h>

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (args[i])
	{
		if (args[i][0] == '-')
		{
			ft_putstr_fd("unset: ", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putstr_fd(": invalid option\n", STDERR_FILENO);
			return (2);
		}
		else
			unset_env(&(shell->env), args[i]);
		i++;
	}
	return (status);
}
