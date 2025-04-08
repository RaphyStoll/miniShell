#include "env_struct.h"
#include "utils.h"
#include "bultin.h"

void builtin_export(t_env *env)
{
	t_env *dup_env = env_dup(env);
	is_valid_identifier(dup_env->type);
	sort_env(&dup_env);

	while (dup_env != NULL)
	{
		printf("%s=%s\n", dup_env->type, dup_env->value);
		dup_env = dup_env->next;
	}
	return ;
}
 //! test
t_env	*init_env(char **env)
{
	t_env	*env_list;
	t_env	*new;
	int		i;
	int		j;

	env_list = NULL;
	i = 0;
	if (!env)
		return NULL;
	while (env[i])
	{
		j = 0;
		while (env[i][j] != '=' && env[i][j])
			j++;
		if (env[i][j] == '=')
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (free_env(env_list), NULL);
			new->type = ft_substr(env[i], 0, j);
			if (!new->type)
				return (free_env(env_list), free(new), NULL);
			new->value = ft_strdup(&env[i][j + 1]);
			if (!new->value)
				return (free_env(env_list), free(new->type), free(new), NULL);
			new->next = NULL;
			add_env_node(&env_list, new);
			if (!env_list)
				return (free_env(env_list), free(new->type), free(new->value), free(new), NULL);
		}
		i++;
	}
	return (env_list);
}

int main (int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_env *env = init_env(envp);
	if (!env)
		return 1;
	builtin_export(env);
	return 0;
}
