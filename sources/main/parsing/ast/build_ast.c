/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:29:02 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/22 02:29:03 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/main/ast.h"
#include "../../../../includes/main/lexing.h"

/**
 * @brief Construit l'arbre de syntaxe abstraite (AST) à partir d'une liste de tokens.
 *
 * @param tokens La liste chaînée de tokens analysés lexicalement.
 * @return Un pointeur vers la racine de l'AST construit, ou NULL si la liste est vide.
 */
t_node	*build_ast(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_logical(&tokens));
}