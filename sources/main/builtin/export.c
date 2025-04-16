#include "env_struct.h"
#include "utils.h"
#include "builtin.h"

int	builtin_export(t_env *env, char *arg)
{
	t_env *dup_env;
	t_env *current;
	
	dup_env = env_dup(env);
	if (arg)
		return (pars_arg(dup_env, arg));
	current = dup_env;
	if (!dup_env)
		return (1);
	while (current != NULL)
	{
		if (is_valid_identifier(current->type))
			return (false);
		current = current->next;
	}
	sort_env(&dup_env);
	current = dup_env;
	while (current != NULL)
	{
		printf("declare -x %s=%s\n", current->type, current->value);
		current = current->next;
	}
	free_env(dup_env);
	free_env(current);
	return (0);
}

static void	join_value(t_env *existing, char *var_value, int plus_concat)
{
	char	*tmp;

	if (plus_concat)
	{
		tmp = ft_strjoin(existing->value, var_value);
		free(existing->value);
		existing->value = tmp;
	}
	else
	{
		free(existing->value);
		existing->value = ft_strdup(var_value);
	}
}

static void	create_new_env(t_env *env, char *var_name, char *var_value)
{
	t_env	*new_env;

	new_env = create_env_node(var_name, var_value);
	add_env_node(&env, new_env);
}

bool	pars_arg(t_env *env, char *arg)
{
	char	*equal_pos;
	char	*var_name;
	char	*var_value;
	t_env	*existing;
	bool	plus_concat;

	if (!arg)
		return (false);
	equal_pos = ft_strchr(arg, '=');
	if (!equal_pos)
		return (false);
	plus_concat = false;
	if (equal_pos != arg && *(equal_pos - 1) == '+')
		plus_concat = true;
	if (plus_concat)
		var_name = ft_substr(arg, 0, (equal_pos - arg) - 1);
	else
		var_name = ft_substr(arg, 0, (equal_pos - arg));
	if (!var_name)
		return (false);
	var_value = ft_strdup(equal_pos + 1);
	if (!var_value)
		return (free(var_name), false);
	existing = find_env(env, var_name);
	if (!existing)
		create_new_env(env, var_name, var_value);
	else
		join_value(existing, var_value, plus_concat);
	return (free(var_name), free(var_value), true);
}

/*
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
*/