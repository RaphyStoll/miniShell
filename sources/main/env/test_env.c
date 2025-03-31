/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 09:56:07 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/29 19:53:09 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/env_struct.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	t_env	*tmp;
	int		j;

	(void)argc;
	(void)argv;

	env_list = init_env(envp);
	tmp = env_list;
	j = 0;
	while (tmp)
	{
		printf("env[%d] = %s=%s\n", j, tmp->type, tmp->value);
		tmp = tmp->next;
		j++;
	}
	return (0);
}