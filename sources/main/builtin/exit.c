/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:22:16 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/01 12:27:38 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "minishell.h"
#include "utils.h"
#include <stdio.h>

static int	error_msg(t_shell *shell, char **args)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(args[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	rl_clear_history();
	free_shell(shell);
	exit(2);
}

static int	error_msg2(t_shell *shell)
{
	int	status;

	rl_clear_history();
	status = shell->last_exit_status;
	free_shell(shell);
	return (status);
}

int	builtin_exit(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	ft_putstr_fd("exit\n", 1);
	if (!args[1])
		return (error_msg2(shell));
	if (args[1][0] == '+' || args[1][0] == '-')
		i++;
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]))
			return (error_msg(shell, args));
		i++;
	}
	if (args[2])
		return (rl_clear_history(), free_shell(shell)
			, ft_putstr_fd(SHELL_NAME, 2)
			, ft_putstr_fd("exit: too many arguments\n", 2), GENERIC_ERROR);
	rl_clear_history();
	i = ft_atoi(args[1]) % 256;
	free_shell(shell);
	return (i);
}
