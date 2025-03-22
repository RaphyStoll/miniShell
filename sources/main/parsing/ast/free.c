#include "../../../../includes/main/ast.h"


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

void	free_all_ast(t_node *ast)
{
	if (ast)
		free_node(ast);
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->args)
		free_args(node->args);
	if (node->redirections)
		free_redirections(node->redirections);
	if (node->child)
		free_node(node->child);
	if (node->brother)
		free_node(node->brother);
	free(node);
}
