/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_exception.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 00:25:26 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/12 00:25:30 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

// Traite les cas spéciaux de redirections en début de commande
bool handle_redirection_exceptions(t_token *token_list)
{
    // Si la liste est vide
    if (!token_list)
        return (true);
    
    // Si le premier token est une redirection
    if (token_list->type == REDIRECT_IN || token_list->type == REDIRECT_OUT ||
        token_list->type == HEREDOC || token_list->type == APPEND)
    {
        // Vérifier que le token suivant existe et est de type WORD
        if (token_list->next == NULL || token_list->next->type != WORD)
        {
            printf(RED"Error: Redirection requires a file name\n"NC);
            return (false);
        }
        
        // Traiter la redirection spéciale (selon votre implémentation)
        printf(YELLOW"Special case: Redirection at the beginning\n"NC);
        
        // Si vous voulez convertir ces cas en une forme plus standard
        // par exemple, convertir "> file" en ": > file"
        // Vous pouvez le faire ici
        
        return (true);
    }
    
    return (true);
}