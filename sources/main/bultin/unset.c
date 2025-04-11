/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:22:19 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/11 16:22:51 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_struct.h"

int	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		unset_env(&(shell->env), args[i]);
		i++;
	}
	return (0);
}
