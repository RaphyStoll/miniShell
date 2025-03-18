/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:24:34 by raphalme          #+#    #+#             */
/*   Updated: 2025/03/18 16:26:38 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main/minishell.h"

	int main(void)
{
    char    *input;
    t_token *tokens;

    // Affichage du prompt et lecture de l'input utilisateur
    input = readline("minishell$ ");
    if (!input)
    {
        // Si readline retourne NULL (ex: CTRL+D), on quitte
        printf("exit\n");
        return EXIT_SUCCESS;
    }
    if (input[0] != '\0')
        add_history(input);

    // Appel de la fonction lexer pour analyser la commande
    tokens = lexer(input);
    if (!tokens)
    {
        fprintf(stderr, "Erreur lors du lexing.\n");
        free(input);
        return EXIT_FAILURE;
    }

    // Initialisation du parsing avec les tokens générés par le lexer
    // if (!init_parsing(tokens))
    // {
    //     fprintf(stderr, "Erreur lors du parsing.\n");
    //     // Ici, pense à libérer les ressources associées aux tokens si nécessaire
    //     free(input);
    //     return EXIT_FAILURE;
    // }

    /* 
       Suite du traitement du minishell...
       Par exemple, lancer l'exécution des commandes analysées.
    */

    // Libération des ressources
    free(input);
    // free_tokens(tokens); // Décommenter si tu as une fonction pour libérer tes tokens

    return EXIT_SUCCESS;
}
