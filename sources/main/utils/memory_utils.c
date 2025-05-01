/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:07:41 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/24 15:34:44 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_all(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->str);
		free(token);
		token = tmp;
	}
}

void	free_tokens(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->str);
		free(current);
		current = next;
	}
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->type)
		free(node->type);
	if (node->value)
		free(node->value);
	if (node)
		free(node);
}

void	free_env(t_env *head)
{
	t_env	*current;
	t_env	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		if (current->type)
			free(current->type);
		if (current->value)
			free(current->value);
		if (current)
			free(current);
		current = next;
	}
}

void	free_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->ast)
		free_all_ast(shell->ast);
	if (shell->env)
		free_env(shell->env);
	if (shell->prompt)
		free(shell->prompt);
	if (shell)
		free(shell);
}
