/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:40:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/29 09:51:47 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"

t_env	*add_env_node(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (*env_list == NULL)
		*env_list = new;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (*env_list);
}

// initialiser les variables d environnement dans le main tout au debut
t_env	*init_env(char **env)
{
	t_env	*env_list;
	t_env	*new;
	int		i;
	int		j;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j] != NULL)
			j++;
		if (env[i][j] == '=')
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return ('\0');
			new->type = ft_substr(env[i], 0, j);
			new->value = ft_strdup(&env[i][j + 1]);
			new->next = NULL;
			add_env_node(&env_list, new);
		}
		i++;
	}
	return (env_list);
}

