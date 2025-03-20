// sert uniquement a print l'ast
#include "../../../../includes/main/ast.h"

void print_ast(t_node *node, int indent)
{
    if (!node)
        return;

    // Affichage de l'indentation
    for (int i = 0; i < indent; i++)
        printf("    ");

    // Affichage du type de nœud
    switch (node->type)
    {
        case AST_COMMAND:
            printf("[CMD: ");
            if (node->args)
            {
                for (int i = 0; node->args[i]; i++)
                {
                    printf("%s ", node->args[i]);
                }
            }
            printf("]");
            break;
        case AST_PIPE:
            printf("[PIPE]");
            break;
        case AST_LOGICAL:
            printf("[LOGICAL]");
            break;
        case AST_GROUP:
            printf("[GROUP]");
            break;
        default:
            printf("[UNKNOWN]");
    }
    printf("\n");

    // Affichage des redirections associées
    if (node->redirections)
    {
        print_redirections(node->redirections, indent + 1);
    }

    // Parcours du premier enfant
    if (node->child)
    {
        print_ast(node->child, indent + 1);
    }
    
    // Parcours des frères (au même niveau)
    if (node->brother)
    {
        print_ast(node->brother, indent);
    }
}


void print_redirections(t_redirection *redir, int indent)
{
    while (redir)
    {
        for (int i = 0; i < indent; i++)
            printf("    ");
        printf("redir: ");
        switch (redir->type)
        {
            case REDIRECT_IN:
                printf("< %s", redir->target);
                break;
            case REDIRECT_OUT:
                printf("> %s", redir->target);
                break;
            case APPEND:
                printf(">> %s", redir->target);
                break;
            case HEREDOC:
                printf("<< %s", redir->target);
                break;
            default:
                printf("unknown");
        }
        printf("\n");
        redir = redir->next;
    }
}