#include "minishell.h"
#include <stdio.h>

int	buildin_exit(t_shell *shell, int error)
{
	free_shell(shell);
	exit(error);
}
