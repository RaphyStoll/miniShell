#include "../../../../includes/main/ast.h"

// Crée un nœud de l'AST avec un type donné et des arguments (NULL si non pertinent)
t_node *create_node(t_node_type type, char **args)
{

}

// Ajoute un enfant à un nœud parent (ex: une commande dans un pipeline)
void add_child(t_node *parent, t_node *child)
{

}

// Ajoute un frère à un nœud (ex: une commande suivante dans un pipeline)
void add_brother(t_node *node, t_node *brother)
{

}

// Ajoute une redirection à un nœud de type commande
void add_redirection(t_node *cmd, t_redirection *redir)
{

}