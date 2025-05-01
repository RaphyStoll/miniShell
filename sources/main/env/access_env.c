/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:07:45 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/01 07:44:55 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "minishell.h"
#include "utils.h"

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
	env = shell->env;
	while (env)
	{
		if (ft_strcmp(env->type, type) == 0)
		{
			value = ft_strdup(env->value);
			if (!value)
				return (free_env(env), NULL);
			return (value);
		}
		env = env->next;
	}
	return (NULL);
}

bool	add_env_to_array(t_env *env, char **envp, int count)
{
	char	*tmp_type;
	char	*entry;

	if (!env->type || !env->value)
		return false;
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
	int		len;
	int		i;

	len = 0;
	tmp = env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
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
	envp[i] = NULL;
	return (envp);
}

t_env	*get_last_node(t_env *dup_env)
{
	if (!dup_env)
		return (NULL);
	while (dup_env->next)
		dup_env = dup_env->next;
	return (dup_env);
}

void	append_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (*env == NULL)
		*env = new_node;
	else
	{
		current = *env;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
}
