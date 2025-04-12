/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:24:59 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/18 16:31:08 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

#ifdef TEST_LEXING
int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("Exiting minishell...\n");
			break;
		}
		if (*input)
			add_history(input);
		tokens = lexer(input);
		if (!tokens)
			printf("Lexer failed\n");
		else
		{
			t_token *tmp = tokens;
			while (tmp)
			{
				printf("Token: \"%s\"(Type: %d)\n", tmp->str, tmp->type);
				tmp = tmp->next;
			}
		}
		free_all(tokens);
		tokens = NULL;
		free(input);
		system("leaks test_lexing | grep 'leaks Report' -A 10");
	}
	clear_history();
	printf("Exiting minishell...\n");
	return 0;
}
#endif
