/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:24:34 by raphalme          #+#    #+#             */
/*   Updated: 2025/04/27 13:27:16 by Charlye          ###   ########.fr       */
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
#include "exec.h"
#include <errno.h>
#include "debbug.h"

/**
 * @brief Global variable used to store the last caught signal number.
 *
 * Only used for signal handling (e.g., SIGINT during prompt input).
 */
int	g_signal = 0;

/**
 * @brief Initializes the shell structure.
 *
 * Sets up environment, signals, and terminal behavior.
 *
 * @param envp Program environment variables.
 * @return Pointer to t_shell or NULL on failure.
 */
t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = init_env(envp);
	if (!shell->env)
		shell->env = init_minimal_env(shell->env);
	if (!init_shell_level(shell))
		return (free_shell(shell), NULL);
	set_signals();
	ignore_ctrl_display();
	shell->prompt = strdup("minishell-0.8$ ");
	if (!shell->prompt)
		return (perror("strdup prompt failed "), free_shell(shell), NULL);
	return (shell);
}

/**
 * @brief Processes a single input line.
 *
 * Performs lexing, parsing, expansion, and execution.
 *
 * @param input User input string.
 * @param shell Shell context.
 * @return true on success, false on error.
 */
bool	process_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	int		flag;

	flag = 0;
	tokens = lexer(input, shell);
	if (!tokens)
		return (false);
	//print_tokens(tokens);
	if (!init_parsing(shell, tokens, &flag) || flag == 1)
		return (free_tokens(tokens), false);
	shell->ast = build_ast(tokens);
	free_tokens(tokens);
	if (!shell->ast)
		return (false);
	//print_ast_debug(shell->ast, 3, "child");
	if (execute_ast(shell->ast, shell))
		if (errno != 0)
			return (false);
	return (true);
}

/**
 * @brief Main shell loop.
 *
 * Reads input, handles signals, and runs commands.
 *
 * @param shell Shell context.
 */
void	loop_shell(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline(shell->prompt);
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		if (process_input(input, shell))
		{
			free_all_ast(shell->ast);
			shell->ast = NULL;
		}
		free(input);
		g_signal = 0;
	}
}

void	loop_non_interactive(t_shell *shell)
{
	char	*input;

	while (1)
	{
		input = readline(NULL);
		if (!input)
			break ;
		if (*input)
		{
			if (process_input(input, shell))
			{
				free_all_ast(shell->ast);
				shell->ast = NULL;
			}
			free(input);
			g_signal = 0;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	int status;

	(void) argc;
	(void) argv;
	shell = init_shell(envp);
	if (!shell)
		return (EXIT_FAILURE);
	if (isatty(STDIN_FILENO))
		loop_shell(shell);
	else
		loop_non_interactive(shell);
	status = shell->last_exit_status;
	free_shell(shell);
	rl_clear_history();
	return (status);
}
