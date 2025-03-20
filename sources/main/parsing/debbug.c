/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debbug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:52 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/18 22:20:27 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/error_code.h"
#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"
#include "../../../includes/main/ast.h"

// Fonction pour afficher la liste de tokens (utile pour débugger)
void	print_tokens(t_token *head)
{
	t_token		*current;
	const char	*type_names[] = {
		"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", 
		"HEREDOC", "APPEND", "AND", "OR", 
		"O_PARENTHESIS", "C_PARENTHESIS"
	};

	current = head;
	printf("Liste des tokens:\n");
	while (current != NULL)
	{
		printf("Token: %-15s | Type: %s\n", current->str, type_names[current->type]);
		current = current->next;
	}
	printf("\n");
}

// Fonction pour afficher uniquement le token actuel
void	print_current_token(t_token *token)
{
	const char	*type_names[] = {
		"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", 
		"HEREDOC", "APPEND", "AND", "OR", 
		"O_PARENTHESIS", "C_PARENTHESIS"
	};

	if (!token)
	{
		printf(GREEN "Token actuel: NULL\n"NC);
		return;
	}
	
	printf(GREEN "Token actuel: %-15s | Type: %s\n"NC, token->str, type_names[token->type]);
	
	// Afficher les tokens adjacents pour le contexte (optionnel)
	if (token->prev)
		printf(GREEN "Token précédent: %-10s | Type: %s\n"NC, token->prev->str, type_names[token->prev->type]);
	else
		printf(GREEN "Token précédent: NULL\n"NC);
		
	if (token->next)
		printf(GREEN "Token suivant:  %-10s | Type: %s\n"NC, token->next->str, type_names[token->next->type]);
	else
		printf(GREEN "Token suivant:  NULL\n"NC);
}

void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		printf("NULL");
		return ;
	}
	i = 0;
	printf("[");
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

//print un noeud de la liste
void	print_node(t_token *current)
{
	printf("(%s) [%d]", current->str, current->type);
}

//print la liste
void	print_list(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current != NULL)
	{
		print_node(current);
		current = current->next;
	}
	ft_putstr_fd("NULL\n", 1);
	return ;
}





// sert uniquement a print l'ast
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

