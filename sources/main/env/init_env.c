/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:40:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/15 18:00:01 by raphaelferr      ###   ########.fr       */
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
t_env	*add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	if (!env_list)
		return NULL;
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (*env_list);
}

t_env	*init_minimal_env(t_env *env)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->type = "PWD";
	new_env->value = getcwd(NULL, 0);
	if (!new_env->value)
		return (free_env(new_env), NULL);
	new_env->next = NULL;
	add_env_node(&env, new_env);
	new_env = new_env->next;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->type = "SHLVL";
	new_env->value = "1";
	new_env->next = NULL;
	add_env_node(&env, new_env);
	new_env = new_env->next;
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	return (new_env->type = "_", new_env->value = "/bin/",
		new_env->next = NULL, add_env_node(&env, new_env), env);
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
