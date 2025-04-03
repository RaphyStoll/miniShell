/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:49:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/03 19:57:44 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ast_struct.h"

extern t_node *malloc_node(t_ast_type type);
extern int add_arg_to_node(t_node *node, char *arg);
extern void print_ast(t_node *node, int level);

int main(void)
{
	// Simule la commande : (ls -la | grep txt) && echo done
	t_node *ls = malloc_node(AST_COMMAND);
	add_arg_to_node(ls, "ls");
	add_arg_to_node(ls, "-la");

	t_node *grep = malloc_node(AST_COMMAND);
	add_arg_to_node(grep, "grep");
	add_arg_to_node(grep, "txt");

	t_node *pipe = malloc_node(AST_PIPE);
	pipe->child = ls;
	pipe->brother = grep;

	t_node *subshell = malloc_node(AST_SUBSHELL);
	subshell->child = pipe;

	t_node *echo = malloc_node(AST_COMMAND);
	add_arg_to_node(echo, "echo");
	add_arg_to_node(echo, "done");

	t_node *logic = malloc_node(AST_LOGICAL);
	logic->logic_type = LOGICAL_AND;
	logic->child = subshell;
	logic->brother = echo;

	//print_ast(logic, 0);
	print_ast_debug(logic, 0, "child");

	free_all_ast(logic);

	return (0);
}