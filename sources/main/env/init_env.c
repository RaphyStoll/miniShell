/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:40:18 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/01 10:56:01 by chpasqui         ###   ########.fr       */
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
		return (NULL);
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
	t_env	*new_env;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	new_env = create_env_node("PWD", cwd);
	free (cwd);
	if (!new_env)
		return (NULL);
	add_env_node(&env, new_env);
	new_env = create_env_node("SHLVL", "1");
	if (!new_env)
		return (free_env(env), NULL);
	add_env_node(&env, new_env);
	new_env = create_env_node("_", "/bin/");
	if (!new_env)
		return (free_env(env), NULL);
	add_env_node(&env, new_env);
	return (env);
}

bool	add_env_from_string(t_env **env_list, char *env)
{
	t_env	*new;
	int		j;

	j = 0;
	while (env[j] != '=' && env[j])
		j++;
	if (env[j] == '=')
	{
		new = ft_calloc(1, sizeof(t_env));
		if (!new)
			return (false);
		new->type = ft_substr(env, 0, j);
		new->value = ft_strdup(&env[j + 1]);
		if (!new->type || !new->value)
			return (free_env_node(new), false);
		new->next = NULL;
		add_env_node(env_list, new);
		return (true);
	}
	return (true);
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
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i])
	{
		if (!add_env_from_string(&env_list, env[i]))
			return (free_env(env_list), NULL);
		i++;
	}
	return (env_list);
}
