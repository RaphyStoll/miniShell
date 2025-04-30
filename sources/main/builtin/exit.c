/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:22:16 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/30 17:23:08 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "minishell.h"
#include "utils.h"
#include "debbug.h"
#include <stdio.h>

int	builtin_exit(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		exit(shell->last_exit_status);
	if (args[1][0] == '+' || args[1][0] == '-')
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		i++;
	}
	if (args[2])
		return (ft_putstr_fd(SHELL_NAME, 2)
			, ft_putstr_fd("exit: too many arguments\n", 2), GENERIC_ERROR);
	exit(ft_atoi(args[1]) % 256);
}
