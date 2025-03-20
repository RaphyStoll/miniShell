/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debbug.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphalme <raphalme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:52 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/20 14:34:13 by raphalme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/error_code.h"
#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"


// Fonction pour afficher la liste de tokens (utile pour débugger)
void	print_tokens(t_token *head)
{
	t_token		*current;
	const char	*type_names[] = {
		"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", 
		"HEREDOC", "APPEND", "AND", "OR", 
		"O_PARENTHESIS", "C_PARENTHESIS"
	};

	current = head;
	printf("Liste des tokens:\n");
	while (current != NULL)
	{
		printf("Token: %-15s | Type: %s\n", current->str, type_names[current->type]);
		current = current->next;
	}
	printf("\n");
}

// Fonction pour afficher uniquement le token actuel
void	print_current_token(t_token *token)
{
	const char	*type_names[] = {
		"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", 
		"HEREDOC", "APPEND", "AND", "OR", 
		"O_PARENTHESIS", "C_PARENTHESIS"
	};

	if (!token)
	{
		printf(GREEN "Token actuel: NULL\n"NC);
		return;
	}
	
	printf(GREEN "Token actuel: %-15s | Type: %s\n"NC, token->str, type_names[token->type]);
	
	// Afficher les tokens adjacents pour le contexte (optionnel)
	if (token->prev)
		printf(GREEN "Token précédent: %-10s | Type: %s\n"NC, token->prev->str, type_names[token->prev->type]);
	else
		printf(GREEN "Token précédent: NULL\n"NC);
		
	if (token->next)
		printf(GREEN "Token suivant:  %-10s | Type: %s\n"NC, token->next->str, type_names[token->next->type]);
	else
		printf(GREEN "Token suivant:  NULL\n"NC);
}

void	print_tab(char **tab)
{
	int	i;

	if (!(tab))
	{
		printf("NULL");
		return ;
	}
	i = 0;
	printf("[");
	while (tab[i])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

//print un noeud de la liste
void	print_node(t_token *current)
{
	printf("(%s) [%d]", current->str, current->type);
}

//print la liste
void	print_list(t_token **head)
{
	t_token	*current;

	current = *head;
	while (current != NULL)
	{
		print_node(current);
		current = current->next;
	}
	ft_putstr_fd("NULL\n", 1);
	return ;
}







