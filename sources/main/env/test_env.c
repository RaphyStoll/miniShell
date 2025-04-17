/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 09:56:07 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/16 23:06:53 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_struct.h"

void	print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->type, env_list->value);
		env_list = env_list->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;

	(void)argc;
	(void)argv;

	env_list = init_env(envp);
	printf("🔹 ENV INITIALE :\n");
	print_env_list(env_list);

	printf("\n🔹 Ajout / modif de PATH et ajout de NOUVELLE_VAR :\n");
	set_env_value(&env_list, "PATH", "/custom/path");
	set_env_value(&env_list, "NOUVELLE_VAR", "test123");
	print_env_list(env_list);

	printf("\n🔹 Suppression de USER :\n");
	unset_env(&env_list, "USER");
	print_env_list(env_list);

	printf("\n🔹 Test get_env_value(\"SHELL\") :\n");
	char *val = get_env_value(env_list, "SHELL");
	if (val)
		printf("Valeur de SHELL = %s\n", val);
	else
		printf("SHELL non trouvée\n");
	free_env(env_list);
	return (0);
}
