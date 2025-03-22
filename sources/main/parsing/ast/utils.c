#include "../../../../includes/main/ast.h"

t_node	*malloc_node(t_ast_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->args = NULL;
	node->redirections = NULL;
	node->child = NULL;
	node->brother = NULL;
	return (node);
}

int	add_arg_to_node(t_node *node, char *arg)
{
	char	**new_args;
	int		len;
	int		i;

	if (!node || !arg)
		return (0);
	len = 0;
	if (node->args)
	{
		while (node->args[len])
			len++;
	}
	new_args = malloc(sizeof(char *) * (len + 2));
	if (!new_args)
		return (0);
	i = 0;
	while (i < len)
	{
		new_args[i] = node->args[i];
		i++;
	}
	new_args[i++] = strdup(arg);
	new_args[i] = NULL;
	free(node->args);
	node->args = new_args;
	return (1);
}

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

int	handle_redirection(t_token **tokens, t_node *node)
{
	t_redirection	*redir;

	if (!tokens || !*tokens || !node)
		return (0);
	if (!(*tokens)->next || (*tokens)->next->type != WORD)
		return (0); // erreur : pas de cible après redirection
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
	redir->target = strdup((*tokens)->next->str);
	redir->next = NULL;
	add_redirection_to_node(node, redir);
	*tokens = (*tokens)->next->next; // skip l'opérateur et sa cible
	return (1);
}

t_node	*parse_command_or_subshell(t_token **tokens)
{
	if (!tokens || !*tokens)
		return (NULL);
	if ((*tokens)->type == O_PARENTHESIS)
		return (parse_subshell(tokens));
	return (parse_command(tokens));
}