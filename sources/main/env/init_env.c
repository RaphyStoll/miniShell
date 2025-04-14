/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:40:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/14 16:27:00 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "../../../lib/libft/header/libft.h"
#include "utils.h"

/**
 * @brief Adds a new t_env node at the end of the environment list.
 * 
 * @param env_list Address of the pointer to the head of the list.
 * @param new Node to add to the list.
 * @return A pointer to the head of the updated list.
 */
t_env	*add_env_node(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (!env_list)
		return NULL;
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

t_env	*init_minimal_env(t_env *env)
{
	t_env	*new;
	char	*type[3];
	char	*value[3];
	int		i;

	type[0] = "PWD";
	type[1] = "SHLVL";
	type[2] = "_";
	value[0] = getcwd(NULL, 0);
	if (!value[0])
		return (free(value[0]), NULL);
	value[1] = "1";
	value[2] = "/usr/bin/";
	if (env == NULL)
	{
		env = malloc(sizeof(t_env));
		if (!env)
			return (env->next = NULL, NULL);
	}
	i = 0;
	while (i < 3)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL);
		new->type = ft_strdup(type[i]);
		if (new->type)
			return (free_env(new), NULL);
		new->value = ft_strdup(value[i]);
		if (new->value)
			return (free_env(new), NULL);
		new->next = NULL;
		add_env_node(&env, new);
		i++;
	}
	return (env);
}

/**
 * @brief Initializes the environment list from the given envp array.
 * 
 * @param env Array of strings in the format VAR=VALUE (envp).
 * @return A pointer to the head of the list, or NULL on failure.
 */
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
		while (env[i][j] != '=' && env[i][j])
			j++;
		if (env[i][j] == '=')
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (NULL);
			new->type = ft_substr(env[i], 0, j);
			new->value = ft_strdup(&env[i][j + 1]);
			new->next = NULL;
			add_env_node(&env_list, new);
		}
		i++;
	}
	return (env_list);
}
