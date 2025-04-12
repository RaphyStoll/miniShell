/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphael <raphael@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:16:33 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/12 21:59:58 by raphael          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"

/**
 * @brief Get the value of a variable from the environment list.
 * 
 * @param env Environment list.
 * @param type Type of variable to search.
 * @return The value associated with the variable, or NULL if not found.
 */
char	*get_env_value(t_shell *shell, char	*type)
{
	t_env	*env;
	char	*value;

	if (!shell || !type)
		return (NULL);
	if (ft_strcmp(type, "?") == 0)
		return (ft_itoa(shell->last_exit_status));
	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->type, type) == 0)
		{
			value = ft_strdup(env->value);
			if (!value)
				return (NULL);
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Converts the environment list into a NULL-terminated array of strings
 * that is adequate for the execve function.
 * 
 * @param env Environment list.
 * @return Array of strings in the format VAR=VALUE.
 */
char	**get_envp(t_env *env)
{
	t_env	*tmp;
	char	**envp;
	char	*tmp_type;
	int		count;

	count = 0;
	tmp = env;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	envp = malloc(sizeof(char *) * (count + 1));
	if (!envp)
		return (NULL);
	count = 0;
	while (env)
	{
		tmp_type = ft_strjoin(env->type, "=");
		envp[count++] = ft_strjoin(tmp_type, env->value);
		free(tmp_type);
		env = env->next;
	}
	envp[count] = NULL;
	return (envp);
}
