/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:24:59 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/17 16:51:14 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

int	main(int argc, char **argv)
{
	t_token	*tokens;

	if (argc != 2)
	{
		printf("Usage : %s \"command to tokenize\"\n", argv[0]);
		return (1);
	}
	tokens = lexer(argv[1]);
	if (!tokens)
	{
		printf("Lexer failed\n");
		return (1);
	}
	printf("Lexer successful, printing tokens:\n");
	while (tokens)
	{
		printf("Token: \"%s\"(Type: %d)\n", tokens->str, tokens->type);
		tokens = tokens->next;
	}
	return (0);
}
