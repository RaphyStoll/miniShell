/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_env2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:35:24 by chpasqui          #+#    #+#             */
/*   Updated: 2025/05/01 12:35:40 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "minishell.h"
#include "utils.h"

bool	add_env_to_array(t_env *env, char **envp, int count)
{
	char	*tmp_type;
	char	*entry;

	if (!env->type || !env->value)
		return (false);
	tmp_type = ft_strjoin(env->type, "=");
	if (!tmp_type)
		return (false);
	entry = ft_strjoin(tmp_type, env->value);
	free(tmp_type);
	if (!entry)
		return (false);
	envp[count] = entry;
	return (true);
}

static int	struct_env_len(t_env *env)
{
	t_env	*tmp;
	int		len;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
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
	char	**envp;
	int		len;
	int		i;

	len = struct_env_len(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (!add_env_to_array(env, envp, i))
		{
			while (i--)
				free(envp[i]);
			return (free(envp), NULL);
		}
		env = env->next;
		i++;
	}
	return (envp[i] = NULL, envp);
}
