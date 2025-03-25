/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_code.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:47:34 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/25 11:06:08 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CODE_H
# define ERROR_CODE_H

//? enum pour les code erreur classique (baser sur le tableau excel)
//$ pas trouver de tableau officiel des code erreur
typedef enum e_error
{
	SUCCESS = 0,				// La commande s'est exécutée avec succès.
	GENERIC_ERROR = 1,			// Erreur générale ou non spécifiée.
	USAGE_ERROR = 2,			// Mauvaise utilisation commande
	MATH_ERROR = 3,				// Erreur mathématique
	MEMORY_ERROR = 8,			// Erreur de mémoire insuffisante.
	SPECIFIC_ERROR_42 = 42,		// Code d'erreur spéc. utilisé par programme
	PERMISSION_ERROR = 86,		// Erreur de permission refusée.
	SYNTAX_ERROR = 102,			// Erreur de syntaxe ou de paramètre incorrect.
	COMMAND_NOT_FOUND = 127,	// La commande spécifiée n'a pas été trouvée.
	WRAPPER_ERROR = 255,		// Erreur dans le wrapper de la commande.
	UNCLOSED_QUOTE = 103,
	UNCLOSED_PARENTHESIS = 104,
}	t_error;

//? enum pour les codes d'erreur des signaux
//$ je les ai separer parce que je pense qu'ils me sont aps destiner
typedef enum e_serror
{
	SIGINT_ERROR = 130,				// Signal SIGINT (2)
	SIGKILL_ERROR = 137,			// Signal SIGKILL (9)
	SIGSEGV_ERROR = 139,			// Signal SIGSEGV (11)
	SIGTERM_ERROR = 143,			// Signal SIGTERM (15)
	SIGBUS_ERROR = 131,				// Signal SIGBUS (10)
	SIGRTMIN_ERROR = 154,			// Signal SIGRTMIN (34)
	SIGSTKFLT_ERROR = 170,			// Signal SIGSTKFLT (16)
	SIGRTMIN_PLUS_8_ERROR = 214,	// Signal SIGRTMIN+8 (42)
	SIGXCPU_ERROR = 252,			// Signal SIGXCPU (24)
	SIGXFSZ_ERROR = 253				// Signal SIGXFSZ (25)
}	t_serror;

#endif