/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:03:11 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/07 16:52:54 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Checks if a command is a shell builtin.
 *
 * @param cmd Command to check.
 * @return true if the command is a builtin, false otherwise.
 */
bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}


/**
 * @brief Executes a shell builtin command. Calls the corresponding builtin 
 * function based on the command.
 *
 * @param args Arguments for the builtin command.
 * @param shell Shell context with environment.
 * @return Exit status of the builtin command.
 */
int	execute_builtin(char **args, t_shell *shell)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (builtin_echo(args));
	if (ft_strcmp(args[0], "cd") == 0)
		return (builtin_cd(args, shell->env));
	if (ft_strcmp(args[0], "pwd") == 0)
		return (builtin_pwd(args));
	if (ft_strcmp(args[0], "export") == 0)
		return (builtin_export(args, shell->env));
	if (ft_strcmp(args[0], "unset") == 0)
		return (builtin_unset(args, shell->env));
	if (ft_strcmp(args[0], "env") == 0)
		return (builtin_env(args, shell->env));
	if (ft_strcmp(args[0], "exit") == 0)
		return (builtin_exit(args, shell));
	return (1);
}
