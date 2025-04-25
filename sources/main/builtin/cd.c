/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:20:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/25 16:48:53 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "minishell.h"
#include "error_code.h"
#include "debbug.h"

char	*cd_exception(t_shell *shell, char **ag)
{
	char *target;
	if (!ag[1])
	{
		target = get_env_value(shell, "HOME");
		if (!target)
			return (ft_putstr_fd("cd: HOME not set", 2), target);
		else
			return (target);
	}
	if (ft_strcmp(ag[1], "~") == 0)
	{
		target = get_env_value(shell, "HOME");
		if (!target)
			return (ft_putstr_fd("cd: HOME not set", 2), target);
	}
	if (ft_strcmp(ag[1], "-") == 0)
	{
		target = get_env_value(shell, "OLDPWD");
		if (!target)
			return (ft_putstr_fd("bash: cd: OLDPWD not set", 2), target);
	}
	return (target);
}


int	builtin_cd(t_shell *shell, char **ag)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;


	if (!ag[1] || ft_strcmp(ag[1], "~") == 0 || ft_strcmp(ag[1], "-") == 0)
		target = cd_exception(shell, ag);
	else
		target = ag[1];
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (perror("cd: getcwd:"), GENERIC_ERROR);
	if (chdir(target) < 0)
		return (perror("cd:"), free(oldpwd), GENERIC_ERROR);
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (perror("cd: getcwd:"), free(oldpwd), 1);
	if (!set_env_value(&shell->env, "OLDPWD", oldpwd)
		|| !set_env_value(&shell->env, "PWD", newpwd))
		return (perror("cd : failed to update env"), free(oldpwd), free(newpwd)
			, GENERIC_ERROR);
	return (free(oldpwd), free(newpwd), SUCCESS);
}
