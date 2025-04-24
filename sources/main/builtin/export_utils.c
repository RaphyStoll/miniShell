/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 23:02:51 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/24 19:24:20 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib/libft/header/libft.h"
#include "env_struct.h"
#include "utils.h"
#include "builtin.h"
#include "debbug.h"

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
