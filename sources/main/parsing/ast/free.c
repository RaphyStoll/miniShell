#include "../../../../includes/main/ast.h"

void free_redirections(t_redirection *redir)
{
    while (redir)
    {
        t_redirection *temp = redir;
        redir = redir->next;
        free(temp->target);
        free(temp);
    }
}

void free_ast(t_node *node)
{
    if (!node)
        return;
    
    // Libérer récursivement l'enfant et le frère
    free_ast(node->child);
    free_ast(node->brother);
    
    // Libérer le tableau d'arguments
    if (node->args)
    {
        for (int i = 0; node->args[i] != NULL; i++)
            free(node->args[i]);
        free(node->args);
    }
    
    // Libérer la liste des redirections
    free_redirections(node->redirections);
    
    // Libérer le nœud lui-même
    free(node);
}