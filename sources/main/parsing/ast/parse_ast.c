#include "../../../../includes/main/ast.h"
#include "../../../../includes/main/lexing.h"


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

t_node	*parse_command(t_token **tokens)
{
	t_node	*node;

	if (!tokens || !*tokens)
		return (NULL);
	node = malloc_node(AST_COMMAND);
	if (!node)
		return (NULL);
	while (*tokens && (*tokens)->type != PIPE
		&& (*tokens)->type != AND
		&& (*tokens)->type != OR
		&& (*tokens)->type != C_PARENTHESIS)
	{
		if ((*tokens)->type == WORD)
		{
			if (!add_arg_to_node(node, (*tokens)->str))
				return (free_all_ast(node), NULL);
		}
		else if ((*tokens)->type == REDIRECT_IN
			|| (*tokens)->type == REDIRECT_OUT
			|| (*tokens)->type == APPEND
			|| (*tokens)->type == HEREDOC)
		{
			if (!handle_redirection(tokens, node))
				return (NULL);
			continue;
		}
		*tokens = (*tokens)->next;
	}
	return (node);
}

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
	if (!*tokens || (*tokens)->type != C_PARENTHESIS)
		return (NULL);
	*tokens = (*tokens)->next;
	return (node);
}

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