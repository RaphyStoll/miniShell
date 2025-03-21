#include "../../../../includes/main/ast.h"

// Crée un nœud de l'AST avec un type donné et des arguments (NULL si non pertinent)
t_node *create_node(t_type type, char **args)
{
	t_node *node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = args;
	node->child = NULL;
	node->brother = NULL;
	node->redirections = NULL;
	return (node);
}

// Ajoute un enfant à un nœud parent (ex: une commande dans un pipeline)
void add_child(t_node *parent, t_node *child)
{
	if (!parent || !child)
		return ;
	if (parent->child == NULL)
		parent->child = child;
	else
		add_brother(parent->child, child);
}

// Ajoute un frère à un nœud (ex: une commande suivante dans un pipeline)
void add_brother(t_node *node, t_node *brother)
{
	t_node *current;

	current = NULL;
	if (!node || !brother)
		return ;
	if (node->brother == NULL)
		node->brother = brother;
	else
	{
		current = node->brother;
		while(current->brother != NULL)
			current = current->brother;
		current->brother = brother;
	}
}

// Ajoute une redirection à un nœud de type commande
void add_redirection(t_node *cmd, t_redirection *redir)
{
	t_redirection *current;

	current = NULL;
	if (!cmd || !redir)
		return;
	if (cmd->redirections == NULL)
		cmd->redirections = redir;
	else
	{
		current = cmd->redirections;
		while (current->next != NULL)
			current = current->next;
		current->next = redir;
	}
}
