#include "../../../includes/main/parsing.h"

bool	if_valide_token(t_token *token)
{
	t_token *current;
	
	current = token;
	while (current != NULL)
	{
		if (current->str == NULL)
			return false;
		if (current->type >= WORD || current->type <= C_PARENTHESIS)
	}
}
