/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:26:49 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/24 12:13:44 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialise et met à jour la variable SHLVL de shell->env.
 *
 * @param shell     Le contexte du shell déjà partiellement initialisé.
 * @return          true si tout s'est bien passé, false sinon.
 */
bool	init_shell_level(t_shell *shell)
{
	char	*lvl_str;

	lvl_str = get_env_value(shell, "SHLVL");
	if (lvl_str)
	{
		shell->shell_level = ft_atoi(lvl_str);
		free(lvl_str);
	}
	else
		shell->shell_level = 0;
	if (shell->shell_level <= 0)
		shell->shell_level = 1;
	else
		shell->shell_level++;
	lvl_str = ft_itoa(shell->shell_level);
	if (!lvl_str)
		return (false);
	set_env_value(&shell->env, "SHLVL", lvl_str);
	free(lvl_str);
	shell->shell_level = shell->shell_level;
	return (true);
}