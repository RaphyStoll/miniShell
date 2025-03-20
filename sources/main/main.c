/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:24:34 by raphalme          #+#    #+#             */
/*   Updated: 2025/03/20 17:53:21 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/main/minishell.h"

void	print_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("Token après parsing: \"%s\" (Type: %d)\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

void	print_current_tokens(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("Token avant parsing: \"%s\" (Type: %d)\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

int	main(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("exit/n");
			break ;
		}
		if (*input)
			add_history(input);
		tokens = lexer(input);
		if (!tokens)
		{
			write(2, "Lexing Error.\n\n", 15);
			free(input);
			continue ;
		}
		if (!init_parsing(tokens) == 0)
		{
			write(2, "Parsing Error.\n\n", 15);
			free_tokens(tokens);
			free(input);
			continue ;
		}
		print_tokens(tokens);
		printf("Parsing succeeded!\n");
		free_tokens(tokens);
		free(input);
		system("leaks minishell| grep 'leaks Report' -A 10");
	}
	clear_history();
	return EXIT_SUCCESS;
}

