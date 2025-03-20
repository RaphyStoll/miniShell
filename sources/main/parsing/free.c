/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:45 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/20 15:27:32 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"
#include "../../../includes/main/ast.h"

void free_all(t_token *token)
{
	(void)token;
	return ;
}

// Fonction pour libérer la liste de tokens
void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}


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