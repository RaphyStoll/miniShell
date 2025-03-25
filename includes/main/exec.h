/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:16:23 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/25 15:54:08 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "../../../../includes/main/ast.h"

void	execute_ast(t_node *ast_node, t_env *env_list);
void	execute_command(t_node *cmd, t_env *env_list);
void	execute_pipe(t_node *pide, t_env *env_list);
void	execute_logical(t_node *logic, t_env *env_list);
void	execute_subshell(t_node *subshell, t_env *env_list);

typedef struct s_env
{
	char			*type;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_exec
{
	t_env	*env_list;
	int		input_fd;
	int		output_fd;
}	t_exec;



#endif