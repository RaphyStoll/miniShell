/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:20:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/12 16:49:05 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "minishell.h"
#include "error_code.h"

// static bool	update_env_value(t_env *cur, char *value)
// {
// 	char	*tmp;

// 	tmp = ft_strdup(value);
// 	if (!tmp)
// 		return (perror("ft_strdup"), false);
// 	free(cur->value);
// 	cur->value = tmp;
// 	return (true);
// }

// bool	update_env(t_env **env, char *type, char *value)
// {
// 	t_env	*current;
// 	t_env	*prev;

// 	if (!env || !type)
// 		return (GENERIC_ERROR);
// 	current = *env;
// 	prev = NULL;
// 	while (current)
// 	{
// 		if (ft_strcmp(current->type, type) == 0)
// 		{
// 			if (update_env_value(current, value))
// 				return (perror("update_env_value failed"), GENERIC_ERROR);
// 			return (SUCCESS);
// 		}
// 		prev = current;
// 		current = current->next;
// 	}
// 	current = create_env_node(type, value);
// 	if (!current)
// 		return (perror("create_env_node failed"), GENERIC_ERROR);
// 	if (prev)
// 		return (prev->next = current, SUCCESS);
// 	else
// 		return (*env = current, SUCCESS);
// }

int	builtin_cd(t_shell *shell, char **args)
{
	char	*target;
	char	*oldpwd;
	char	*newpwd;

	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		target = get_env_value(shell->env, "HOME");
		if (!target)
			return (perror("cd: HOME not set"), GENERIC_ERROR);
	}
	else
		target = args[1];
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
