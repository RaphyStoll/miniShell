/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debbug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:29:29 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/22 02:29:30 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/main/ast.h"


static void	print_branch_prefix(int level, int is_last)
{
	int	i;

	i = 0;
	while (i < level - 1)
	{
		printf("│   ");
		i++;
	}
	if (level > 0)
	{
		if (is_last)
			printf("└── ");
		else
			printf("├── ");
	}
}

static const char	*ast_type_to_str(t_ast_type type)
{
	if (type == AST_COMMAND)
		return ("COMMAND");
	if (type == AST_PIPE)
		return ("PIPE");
	if (type == AST_LOGICAL)
		return ("LOGICAL");
	if (type == AST_SUBSHELL)
		return ("SUBSHELL");
	return ("UNKNOWN");
}

static const char	*logic_type_to_str(t_logical_type type)
{
	if (type == LOGICAL_AND)
		return ("&&");
	if (type == LOGICAL_OR)
		return ("||");
	return ("?");
}

//! focntion pour print ast visuellement
void	print_ast(t_node *node, int level)
{
	t_redirection	*redir;
	int				i;
	int				is_last;

	while (node)
	{
		is_last = (node->brother == NULL);
		print_branch_prefix(level, is_last);
		printf("[%s", ast_type_to_str(node->type));
		if (node->type == AST_LOGICAL)
			printf(": %s", logic_type_to_str(node->logic_type));
		printf("]");
		if (node->args)
		{
			printf(" args:");
			i = 0;
			while (node->args[i])
				printf(" %s", node->args[i++]);
		}
		printf("\n");
		redir = node->redirections;
		while (redir)
		{
			print_branch_prefix(level + 1, 1);
			printf("redir: type=%d target=%s\n", redir->type, redir->target);
			redir = redir->next;
		}
		if (node->child)
			print_ast(node->child, level + 1);
		node = node->brother;
	}
}

//! focntion pour printf l'ast en mode debug
void	print_ast_debug(t_node *node, int level, const char *label)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (i < level)
	{
		printf("│   ");
		i++;
	}
	printf("%s: %s", label, ast_type_to_str(node->type));
	if (node->type == AST_LOGICAL)
		printf(" (%s)", logic_type_to_str(node->logic_type));
	if (node->args)
	{
		printf(" args:");
		i = 0;
		while (node->args[i])
		{
			printf(" \"%s\"", node->args[i]);
			i++;
		}
	}
	printf("\n");
	if (node->child)
		print_ast_debug(node->child, level + 1, "child");
	if (node->brother)
		print_ast_debug(node->brother, level, "brother");
}
