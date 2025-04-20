/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:45:28 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/21 00:46:11 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_STRUCT_H
# define ENV_STRUCT_H

# include <stdio.h>
# include <stdbool.h>

typedef struct s_shell	t_shell;

typedef struct s_env
{
	char			*type;
	char			*value;
	struct s_env	*next;
}	t_env;

t_env	*add_env_node(t_env **env_list, t_env *new);
t_env	*init_env(char **env);
char	**get_envp(t_env *env);
char	*get_env_value(t_shell *shell, char	*type);
void	unset_env(t_env **env, char *type);
void	env_delone(t_env *node);
bool	set_env_value(t_env **env_list, char *type, char *value);
t_env	*create_env_node(char *type, char *value);
t_env	*init_minimal_env(t_env *env);
t_env	*get_last_node(t_env *dup_env);
void	append_node(t_env **env, t_env *new_node);
void	remplace_node(t_env **env, t_env *old_node, t_env *new_node);

#endif