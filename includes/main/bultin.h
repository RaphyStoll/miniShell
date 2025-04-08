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

//!export
bool is_valid_identifier(const char *str);
t_env	*add_env_node(t_env **env_list, t_env *new_node);
void builtin_export(t_env *env);
#endif