/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:29:02 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/13 15:08:36 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "lexing_struct.h"

/**
 * @brief contruct all AST leave a token list.
 *
 * @param tokens list of tokens generated on lexing part.
 * @return a pointer for the head of ast or NULL is list is empty
 */
t_node	*build_ast(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_logical(&tokens));
}
