/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 11:30:03 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/12 18:51:20 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/env_struct.h"
#include "builtin.h"
//# include "error_code.h"
//# include "../../../lib/libft/header/libft.h"

/**
 * @brief Prints the environment variables.
 * 
 * This function iterates over the linked list of environment variables
 * and prints each one in the format "KEY=VALUE" to the standard output.
 * @param env A pointer to the head of the environment variables linked list.
 */
int	builtin_env(t_env *env)
{
	t_env	*cur;

	cur = env;
	while (cur != NULL)
	{
		printf("%s=%s\n", cur->type, cur->value);
		cur = cur->next;
	}
	return (0);
}
