/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_ast_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 21:49:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/04 15:06:23 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quote_type.h"
#include "ast.h"
#include "ast_struct.h"
#include "libft.h"


extern t_node *malloc_node(t_ast_type type);
extern int add_arg_to_node(t_node *node, char *arg, t_quote quote_type);
extern void print_ast(t_node *node, int level);
extern void add_redirection_to_node(t_node *node, t_redirection *redir);

int main(void)
{
	// Simule la commande : (ls -la | grep txt) && echo done
	t_node *ls = malloc_node(AST_COMMAND);
	add_arg_to_node(ls, "ls", QUOTE_NONE);
	add_arg_to_node(ls, "-la", QUOTE_NONE);

	t_node *grep = malloc_node(AST_COMMAND);
	add_arg_to_node(grep, "grep", QUOTE_NONE);
	add_arg_to_node(grep, "txt", QUOTE_NONE);

	t_node *pipe = malloc_node(AST_PIPE);
	pipe->child = ls;
	pipe->brother = grep;

	t_node *subshell = malloc_node(AST_SUBSHELL);
	subshell->child = pipe;

	t_node *echo = malloc_node(AST_COMMAND);
	add_arg_to_node(echo, "echo", QUOTE_NONE);
	add_arg_to_node(echo, "done", QUOTE_NONE);

	t_node *logic = malloc_node(AST_LOGICAL);
	logic->logic_type = LOGICAL_AND;
	logic->child = subshell;
	logic->brother = echo;

	// Simule la commande : echo "hello world" > "output.txt"
	t_node *echo2 = malloc_node(AST_COMMAND);
	add_arg_to_node(echo2, "echo", QUOTE_NONE);
	add_arg_to_node(echo2, "hello world", QUOTE_DOUBLE);

	t_redirection *redir = malloc(sizeof(t_redirection));
	redir->type = REDIRECTION_OUT;
	redir->target = ft_strdup("output.txt");
	redir->quote_type = QUOTE_DOUBLE;
	redir->next = NULL;
	add_redirection_to_node(echo2, redir);

	t_node *root = malloc_node(AST_PIPE);
	root->child = logic;
	root->brother = echo2;

	print_ast_debug(root, 0, "child");
	return (0);
}