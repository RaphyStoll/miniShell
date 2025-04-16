#include "env_struct.h"
#include "utils.h"
#include "builtin.h"

bool	builtin_export(t_env **env, char *arg)
{
	t_env *dup_env;
	t_env *new_node;

	dup_env = env_dup(env);
	if (!dup_env)
		return (false);
	if (arg)
	{
		if (!pars_arg(dup_env, arg))
			return (free_env(dup_env), false);
		new_node = get_last_lode(dup_env);
		if (!env_update(env, new_node))
			return (free_env(dup_env), false);
	}
	display_export(dup_env);
	free_env(dup_env);
	return (true);
}

static bool	env_update(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!env || !new_node)
		return false;
	if (*env == NULL) 
		*env = new_node;
	else
	{
		tmp = *env;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (true);
}

static bool	pars_arg(t_env **env, char *arg)
{

}

static void	display_export(t_env *env)
{

}
