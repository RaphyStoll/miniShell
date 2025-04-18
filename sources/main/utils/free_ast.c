/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:08:09 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/06 12:29:02 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ast_struct.h"

/**
 * @brief Libère une liste de redirections.
 * @param redir Liste à libérer.
 */
void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

/**
 * @brief Libère un tableau de chaînes.
 * @param args Tableau à libérer.
 */
void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

/**
 * @brief Libère un nœud et ses sous-éléments.
 * @param node Nœud à libérer.
 */
void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	if (node->arg_quotes)
		free(node->arg_quotes);
	if (node->redirections)
		free_redirections(node->redirections);
	if (node->child)
		free_node(node->child);
	if (node->brother)
		free_node(node->brother);
	free(node);
}

/**
 * @brief Libère un AST complet.
 * @param ast Racine de l’AST.
 */
void	free_all_ast(t_node *ast)
{
	if (ast)
		free_node(ast);
}
