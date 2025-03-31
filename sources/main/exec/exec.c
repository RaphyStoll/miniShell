/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:20:29 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/31 15:30:45 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute_ast(t_node *ast_node, t_env *env_list)
{
	if (!ast_node)
		return ;
	if (ast_node->type == AST_COMMAND)
	{
		expand_variable(ast_node, env_list);
		execute_commande(ast_node, env_list);
	}
	else if (ast_node->type == AST_PIPE)
		execute_pipe(ast_node, env_list);
	else if (ast_node->type == AST_LOGICAL)
		execute_logical(ast_node, env_list);
	else if (ast_node->type == AST_GROUP)
		execute_subshell(ast_node, env_list);
}

bool	is_builtin(char *cmd)
{
	if (!cmd)
		return (false)
	if ()
	// list : 
	// echo cd pwdexport unset env exit
}


void	execute_pipe(t_node *pide, t_env *env_list)
{
	
}
void	execute_logical(t_node *logic, t_env *env_list)
{
	
}

void	execute_subshell(t_node *subshell, t_env *env_list)
{
	
}