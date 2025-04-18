/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:24:34 by raphalme          #+#    #+#             */
/*   Updated: 2025/04/17 12:02:58 by chpasqui         ###   ########.fr       */
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
	shell->shell_level = ft_atoi(get_env_value(shell, "SHLVL"));
	shell->shell_level++;
	set_env_value(&shell->env,"SHLVL", ft_itoa(shell->shell_level));
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

	tokens = lexer(input);
	if (!tokens)
	{
		return (false);
	}
	if (!init_parsing(tokens))
	{
		free_tokens(tokens);
		return (false);
	}
	shell->ast = build_ast(tokens);
	free_tokens(tokens);
	if (!shell->ast)
		return (false);
	if (execute_ast(shell->ast, shell))
	{
		if (errno != 0)
			return (false);
	}
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
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void) argc;
	(void) argv;
	shell = init_shell(envp);
	if (!shell)
		return (EXIT_FAILURE);
	loop_shell(shell);
	free_shell(shell);
	rl_clear_history();
	return (EXIT_SUCCESS);
}
