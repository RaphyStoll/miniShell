#include "../../../includes/main/error_code.h"
#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"


void	print_token(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->next != NULL)
	{
		printf("Type : %d, [%s]\n", tmp->type, tmp->str);
		tmp = tmp->next;
	}
	printf("Type : %d, [%s]\n",  tmp->type, tmp->str);
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

