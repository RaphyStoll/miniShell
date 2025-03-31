/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:16:33 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/31 11:54:48 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"

// pour trouver la value dans expand variable
char	*get_env_value(t_env *env, char	*type)
{
	while (env)
	{
		if (ft_strcmp(env->type, type) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

// permet de convertir env_list pour execve
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
