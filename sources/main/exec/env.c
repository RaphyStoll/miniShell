/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:40:45 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/25 16:30:07 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/main/exec.h"

// initialiser les variables d environnement dans le main tout au debut
t_env	*init_env(char **env)
{
	
}

// a faire avant d executer une commande
void	expand_variables(t_node *node, t_env *env_list)
{
	
}

// pour trouver la value dans expand variable
char	*get_env_value(t_env *env_list, char *type)
{
	
}

// permet de convertir env_list pour execve
char	**get_envp(t_env*env_list)
{
	
}