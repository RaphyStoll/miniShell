/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:24:34 by raphalme          #+#    #+#             */
/*   Updated: 2025/04/12 15:55:13 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexing.h"
#include "lexing_struct.h"
#include "utils.h"
#include "colors.h"
#include "signals.h"
#include "parsing.h"
#include "ast_struct.h"
#include "ast.h"

int	g_signal = 0;

void	init_shell(t_shell *s, char **envp)
{
	s = ft_calloc(1, sizeof(t_shell));
	if (!s)
		return NULL;
	s->env = init_env(envp);
	set_signals();
	ignore_ctrl_display();
}


bool	set_input(char **input)
{
	if (g_signal == SIGINT)
	{
		handle_signals();
		if (input)
		free(input);
		return true;
	}
	if (!input)
	{
		printf("exit");
		return false ;
		
	}
	if (*input)
	add_history(input);
}

bool	next_step(char **input,t_token *tokens, t_shell *shell)
{
	tokens = lexer(input);
	if (!tokens)
	{
		return (perror("Lexing Error :"), free(input), false);
		free(input);
	}
	if (!init_parsing(tokens))
	{
		return (perror("Parsing Error :"), free_tokens(tokens), false);
		shell->ast = build_ast(tokens);
	}
	if (!shell->ast)
	{
		return (perror("AST Error :"), free(tokens), false);
		free(tokens);
	}
	if (!expand_variables(shell->ast, shell->env))
		return (perror("Expand Error :"), free(shell), false);
	if (!execute_ast(()))
		return (perror("Execution Error :"), free_shell(shell), false);
	return (true);
}

int	loop_shell(char *input, t_token *tokens, t_shell *shell)
{
	while (1)
	{
		free_shell(shell);
		input = readline("minishell-0.2$ ");
		if (!set_input)
			continue ;
		else
			break ;
		if (!next_step(input, tokens, shell))
		{

			continue ;
		}
		else
		{

			continue ;
		}
	}
	free_shell(shell);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	t_token	*tokens;
	char	*input;

	(void) argc;
	(void) argv;
	init_shell(shell, envp);
	loop_shell(input, tokens, shell);
}