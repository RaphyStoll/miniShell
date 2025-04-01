/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:40:45 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/01 15:49:11 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	expand_redirections(t_node *node, t_env *env)
{
	
}

char	expand_one_arg(char *arg, t_env *env)
{
	char	*result;
	int		i;

	result = NULL;
	while (arg[i])
	{
		if (arg[i] != '$')
			result[i] == arg
	}

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

/**
 * @brief Expands variables in command arguments based on quote type.
 *
 * Only arguments without quotes or with double quotes will be expanded.
 * Arguments inside single quotes are left untouched.
 *
 * @param node AST command node whose arguments may be expanded.
 * @param env Environment variable list 
 */
void	expand_variables(t_node *node, t_env *env)
{
	char	**args;
	char	*new_arg;
	int		quote_type;
	int		i;

	i = 0;
	args = node->args;
	while (args[i])
	{
		quote_type = node->arg_quotes[i];
		if (quote_type == QUOTE_NONE || quote_type == QUOTE_DOUBLE)
		{
			new_arg = expand_one_arg(args[i], env);
			free(args[i]);
			args[i] = new_arg;
		}
		i++;
	}
