/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 14:24:59 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/01 12:30:14 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

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
				printf("Token: \"%s\" (Type: %d, Quote: %d)\n", tmp->str, tmp->type, tmp->quote_type);
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
