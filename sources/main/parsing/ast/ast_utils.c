/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 02:28:52 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/07 14:25:32 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "ast_struct.h"
#include "../../../../lib/libft/header/libft.h"

/**
 * @brief Allocate memory for a AST node.
 * @param type type of node.
 * @return new node or NULL.
 */
t_node	*malloc_node(t_ast_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->arg_quotes = NULL;
	node->redirections = NULL;
	node->child = NULL;
	node->brother = NULL;
	return (node);
}

/**
 * @brief Reallocates and expands the arguments and their quote types for a node.
 * 
 * @param node Target AST node to modify.
 * @param arg New argument to add.
 * @param quote_type Quote type of the argument.
 * @param len Current number of arguments before expansion.
 * @return 1 on success, 0 on failure.
 */
int	realloc_arg(t_node *node, char *arg, t_quote quote_type, int len)
{
	char			**new_args;
	t_quote			*new_quotes;
	int				i;

	new_args = malloc(sizeof(char *) * (len + 2));
	if (!new_args)
		return (0);
	new_quotes = malloc(sizeof(t_quote) * (len + 1));
	if (!new_quotes)
		return (free(new_args), 0);
	i = 0;
	while (i < len)
	{
		new_args[i] = node->args[i];
		new_quotes[i] = node->arg_quotes[i];
		i++;
	}
	new_args[i] = ft_strdup(arg);
	new_args[i + 1] = NULL;
	new_quotes[i] = quote_type;
	free(node->args);
	free(node->arg_quotes);
	node->args = new_args;
	node->arg_quotes = new_quotes;
	return (1);
}

/**
 * @brief ADD a arg to a node
 * @param node target node.
 * @param arg arg to add.
 * @return 1 is succes, 0 is false.
 */
int	add_arg_to_node(t_node *node, char *arg, t_quote quote_type)
{
	int	len;
	(void) quote_type;

	if (!node || !arg)
		return (0);
	len = 0;
	if (node->args)
		while (node->args[len])
			len++;
	return (realloc_arg(node, arg, quote_type, len));
}

/**
 * @brief add a redirection to a node
 * @param node target node.
 * @param redir redirection need add in the node.
 */
void	add_redirection_to_node(t_node *node, t_redirection *redir)
{
	t_redirection	*cur;

	if (!node || !redir)
		return ;
	if (!node->redirections)
	{
		node->redirections = redir;
		return ;
	}
	cur = node->redirections;
	while (cur->next)
		cur = cur->next;
	cur->next = redir;
}

/**
 * @brief Handles a redirection in the tokens.
 * @param tokens List of tokens.
 * @param node target node.
 * @return 1 is succes, 0 is false.
 */
int	handle_redirection(t_token **tokens, t_node *node)
{
	t_redirection	*redir;

	if (!tokens || !*tokens || !node)
		return (0);
	if (!(*tokens)->next || (*tokens)->next->type != WORD)
		return (0);
	redir = malloc(sizeof(t_redirection));
	if (!redir)
		return (0);
	if ((*tokens)->type == REDIRECT_IN)
		redir->type = REDIRECTION_IN;
	else if ((*tokens)->type == REDIRECT_OUT)
		redir->type = REDIRECTION_OUT;
	else if ((*tokens)->type == APPEND)
		redir->type = REDIRECTION_APPEND;
	else
		redir->type = REDIRECTION_HEREDOC;
	redir->target = ft_strdup((*tokens)->next->str);
	redir->quote_type = (*tokens)->next->quote_type;
	redir->next = NULL;
	add_redirection_to_node(node, redir);
	*tokens = (*tokens)->next->next;
	return (1);
}
