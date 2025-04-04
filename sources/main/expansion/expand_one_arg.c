/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_one_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:44:37 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/04 14:59:07 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"

/**
 * @brief Expands all variables inside a single argument.
 *
 * @param arg The argument string to process.
 * @param env Environment variable list
 * @return A new allocated string with expanded content, or NULL on failure.
 */
char	*expand_one_arg(char *arg, t_env *env)
{
	char	*result;
	int		i;

	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			i++;
			if (arg[i] == '?')
			{
				i++;
				if (!handle_exit_status(&result))
					return (free(result), NULL);
			}
			else if (!handle_variable(&result, arg, &i, env))
				return (free(result), NULL);
		}
		else if (!handle_regular_char(&result, arg[i++]))
			return (free(result), NULL);
	}
	return (result);
}