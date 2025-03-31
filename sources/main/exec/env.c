/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:40:45 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/31 16:02:22 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	expand_one_arg(char *arg, t_env *env)
{
	char	*result;
	int	i;
	
	while (arg[i])
	{
		if (arg[i] != '$')
			result[i] == arg
	}
}

/**
 * @brief Expands environment variables in a given node's arguments.
 * 
 * This function iterates through the arguments of a command node and replaces
 * any env variable references (e.g., $VAR) with their corresponding values
 * from the environment list.
 * 
 * @param node The command node containing the arguments to expand.
 * @param env_list environment list used to look up variable values.
 */
void	expand_variables(t_node *node, t_env *env)
{
	char	**args;
	char	*type;
	char	*value;
	int		i;

	i = 0;
	args = node->args;
	while (args[i])
	{
		if (args[i][0] == '$' && args[i][1])
		{
			type = ft_strdup(&args[i][1]);
			value = get_env_value(env, type);
			free(args[i]);
			if (value)
				args[i] = ft_strdup(value);
			else
				args[i] = ft_strdup("");
			free(type);
		}
		i++;
	}
}