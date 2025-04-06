#ifndef BULTIN_H
# define BULTIN_H

# include "env_struct.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/errno.h>

int builtin_pwd(void);
int bultin_echo(char **args);
void bultin_env(t_env *env);
int	bultin_echo(char **args);

#endif