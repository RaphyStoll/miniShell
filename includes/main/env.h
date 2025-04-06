#ifndef ENV
# define ENV
# include "env_struct.h"
# include "minishell.h"

t_env	*add_env_node(t_env **env_list, t_env *new_node);
t_env	*init_env(char **env);
char	**get_envp(t_env *env);
char	*get_env_value(t_env *env, char	*type);
void	unset_env(t_env **env, char *type);
void	env_delone(t_env *node);
bool	set_env_value(t_env **env_list, char *type, char *value);
t_env	*create_env_node(char *type, char *value);

#endif