/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:02:51 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/05/01 12:12:18 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "env_struct.h"
#include "utils.h"
#include "builtin.h"

bool	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!str || str[0] == '\0')
		return (false);
	if (!((str[0] >= 'a' && str[0] <= 'z')
			|| (str[0] >= 'A' && str[0] <= 'Z')
			|| str[0] == '_'))
		return (false);
	while (str[i])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
				|| (str[i] >= 'A' && str[i] <= 'Z')
				|| (str[i] >= '0' && str[i] <= '9')
				|| str[i] == '_'))
			return (false);
		i++;
	}
	return (true);
}

t_env	*find_node(t_env *env, char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->type, var_name) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

bool	parse_key_value(char *arg, char **key, char **value, bool *append)
{
	char	*equal_sign;
	int		key_len;

	*append = false;
	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (false);
	if (equal_sign > arg && *(equal_sign - 1) == '+')
		*append = true;
	key_len = equal_sign - arg;
	if (*append)
		key_len--;
	*key = ft_substr(arg, 0, key_len);
	if (!*key || !is_valid_identifier(*key))
		return (false);
	*value = ft_strdup(equal_sign + 1);
	if (!*value)
		return (free(*key), false);
	return (true);
}

bool	process_export_arg(t_env **env, char *arg)
{
	char	*key;
	char	*value;
	bool	append;
	t_env	*new_node;

	if (ft_strchr(arg, '='))
	{
		if (!parse_key_value(arg, &key, &value, &append))
			return (ft_putstr_fd("minishell: export: ", 2), ft_putstr_fd(arg, 2)
				, ft_putstr_fd(": not a valid identifier\n", 2), false);
		new_node = create_env_node(key, value);
		multi_free(key, value);
		if (!new_node || !handle_assignment(env, new_node, append))
			return (false);
	}
	else if (is_valid_identifier(arg))
	{
		new_node = create_env_node(arg, NULL);
		if (!new_node || !handle_assignment(env, new_node, false))
			return (false);
	}
	else
		return (ft_putstr_fd("minishell: export: ", 2), ft_putstr_fd(arg, 2)
			, ft_putstr_fd(": not a valid identifier\n", 2), false);
	return (true);
}

void	multi_free(char *key, char *value)
{
	free(key);
	free(value);
}
