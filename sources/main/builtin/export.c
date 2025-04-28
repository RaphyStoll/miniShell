/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:04:08 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/28 09:57:43 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"
#include "utils.h"
#include "builtin.h"
#include "debbug.h"

bool	builtin_export(t_env **env, char **args)
{
	t_env	*dup_env;
	int		i;
	bool	all_valid;

	dup_env = env_dup(*env);
	if (!dup_env)
		return (GENERIC_ERROR);
	all_valid = true;
	if (args[1])
	{
		i = 1;
		while (args[i])
		{
			if (!process_export_arg(env, args[i]))
				all_valid = false;
			i++;
		}
	}
	else
		display_export(dup_env);
	free_env(dup_env);
	return (all_valid ? SUCCESS : USAGE_ERROR);
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
