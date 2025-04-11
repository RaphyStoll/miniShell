#include "minishell.h"
#include "env_struct.h"

int builtin_unset(t_shell *shell, char **args)
{
	int i;

	i = 0;
	while(args[i])
	{
		unset_env(&(shell->env), args[i]);
		i++;
	}
	return (0);
}