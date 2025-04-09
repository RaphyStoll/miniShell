/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:24:34 by raphalme          #+#    #+#             */
/*   Updated: 2025/04/09 16:40:11 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexing.h"
#include "lexing_struct.h"
#include "colors.h"
#include "signals.h"
#include "parsing.h"
#include "ast_struct.h"
#include "ast.h"

//! pour les test
#include "ast.h"

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

void	init_shell(t_shell *s)
{
	s = malloc(sizeof(t_shell));
	if (!s)
		return NULL;
	s->env = NULL;
	s->ast = NULL;
	s->ast = build_ast;
}

int	main(void)
{
	char	*input;
	t_token	*tokens;
	t_shell	*shell;
	set_signals();
	init_shell(shell);
	ignore_ctrl_display();
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
		{
			printf("minishell$ exit\n");
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
		printf(GREEN"token and verif succeeded!\n"NC);
		print_ast_debug(shell->ast, 0, "child");
		free_tokens(tokens);
		free(input);
		system("leaks minishell| grep 'leaks Report' -A 10");
	}
	if(!input)
		free(input);
	rl_clear_history();
	return EXIT_SUCCESS;
}

void	minishell(void)
{
	char *input;
	
	set_signals();

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
			if (*input)
				add_history(input);
		handle_signal();
	}
}

