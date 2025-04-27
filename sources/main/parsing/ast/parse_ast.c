/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:28:55 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/24 16:43:22 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ast_struct.h"
#include "lexing_struct.h"

/**
 * @brief Pars logical operator (&&, ||).
 * @param tokens token list for parsing.
 * @return head of the AST.
 */
t_node	*parse_logical(t_token **tokens)
{
	t_node	*left;
	t_node	*node;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_pipe(tokens);
	while (*tokens && ((*tokens)->type == AND || (*tokens)->type == OR))
	{
		node = malloc_node(AST_LOGICAL);
		if (!node)
			return (free_all_ast(left), NULL);
		node->logic_type = LOGICAL_AND;
		if ((*tokens)->type == OR)
			node->logic_type = LOGICAL_OR;
		node->child = left;
		*tokens = (*tokens)->next;
		node->brother = parse_pipe(tokens);
		left = node;
	}
	return (left);
}

/**
 * @brief Pars a command.
 * @param tokens token list for parsing.
 * @return head of the AST.
 */
t_node	*parse_command(t_token **token)
{
	t_node	*node;

	if (!token || !*token)
		return (NULL);
	node = malloc_node(AST_COMMAND);
	if (!node)
		return (NULL);
	while (*token && (*token)->type != PIPE && (*token)->type != AND
		&& (*token)->type != OR && (*token)->type != C_PARENTHESIS)
	{
		if ((*token)->type == WORD)
		{
			if (!add_arg_to_node(node, (*token)->str, (*token)->quote_type))
				return (free_all_ast(node), NULL);
		}
		else if ((*token)->type == REDIRECT_IN || (*token)->type == REDIRECT_OUT
			|| (*token)->type == APPEND || (*token)->type == HEREDOC)
		{
			if (!handle_redirection(token, node))
				return (NULL);
			continue ;
		}
		*token = (*token)->next;
	}
	return (node);
}

/**
 * @brief Parse a subshell ("(", ")")
 * @param tokens token list for parsing.
 * @return head of the AST.
 */
t_node	*parse_subshell(t_token **tokens)
{
	t_node	*node;

	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type != O_PARENTHESIS)
		return (NULL);
	node = malloc_node(AST_SUBSHELL);
	if (!node)
		return (NULL);
	*tokens = (*tokens)->next;
	node->child = parse_logical(tokens);
	if (node->child)
		if (!*tokens || (*tokens)->type != C_PARENTHESIS)
			return (NULL);
	*tokens = (*tokens)->next;
	return (node);
}

/**
 * @brief Parse a pipe
 * @param tokens token list for parsing.
 * @return head of the AST.
 */
t_node	*parse_pipe(t_token **tokens)
{
	t_node	*left;
	t_node	*node;

	if (!tokens || !*tokens)
		return (NULL);
	left = parse_command_or_subshell(tokens);
	while (*tokens && (*tokens)->type == PIPE)
	{
		node = malloc_node(AST_PIPE);
		if (!node)
			return (NULL);
		node->child = left;
		*tokens = (*tokens)->next;
		node->brother = parse_command_or_subshell(tokens);
		left = node;
	}
	return (left);
}

/**
 * @brief Pars a command or a subshell.
 * @param tokens token list for parsing.
 * @return head of the AST.
 */
t_node	*parse_command_or_subshell(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == O_PARENTHESIS)
		return (parse_subshell(tokens));
	return (parse_command(tokens));
}
