/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:04:08 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/16 23:05:34 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "utils.h"
#include "builtin.h"

bool	builtin_export(t_env **env, char *arg)
{
	t_env	*dup_env;
	t_env	*new_node;
	t_env	*clone;

	dup_env = env_dup(*env);
	if (!dup_env)
		return (false);
	if (arg)
	{
		if (!pars_arg(&dup_env, arg))
			return (free_env(dup_env), false);
		new_node = get_last_node(dup_env);
		if (!new_node)
			return (free_env(dup_env), false);
		clone = create_env_node(new_node->type, new_node->value);
		if (!clone)
			return (free_env(dup_env), false);
		if (!env_update(env, clone))
			return (free_env(dup_env), free_env(clone), false);
	}
	else
		display_export(dup_env);
	free_env(dup_env);
	return (true);
}

bool	env_update(t_env **env, t_env *new_node)
{
	t_env	*exist;

	if (!env || !new_node)
		return (false);
	exist = find_node(*env, new_node->type);
	if (exist)
		remplace_node(env, exist, new_node);
	else
		append_node(env, new_node);
	return (true);
}

bool	pars_arg(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	bool	append;
	t_env	*new_node;

	if (!parse_key_value(arg, &key, &value, &append))
		return (false);
	new_node = create_env_node(key, value);
	free(key);
	free(value);
	if (!new_node)
		return (false);
	return (handle_assignment(env, new_node, append));
}

bool	handle_assignment(t_env **env, t_env *new_node, bool append)
{
	t_env	*existing;
	char	*joined;

	existing = find_node(*env, new_node->type);
	if (existing)
	{
		if (append && existing->value && new_node->value)
		{
			joined = ft_strjoin(existing->value, new_node->value);
			if (!joined)
				return (free_env(new_node), false);
			free(existing->value);
			existing->value = joined;
			free_env(new_node);
		}
		else
			remplace_node(env, existing, new_node);
	}
	else
		append_node(env, new_node);
	return (true);
}

void	display_export(t_env *env)
{
	t_env	*sorted;
	t_env	*cur;

	sorted = env_dup(env);
	if (!sorted)
		return ;
	sort_env(&sorted);
	cur = sorted;
	while (cur)
	{
		if (cur->value)
			printf("declare -x %s=\"%s\"\n", cur->type, cur->value);
		else
			printf("declare -x %s\n", cur->type);
		cur = cur->next;
	}
	free_env(sorted);
}
