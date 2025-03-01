#include "../../../includes/main/parsing.h"

// Fonction d'initialisation du parsing (à implémenter)
void init_parsing(t_token *tokens) {
	//t_command *cmd;
	
	if (if_valide_token(tokens))
	{
		printf("tokken error\n");
		return ;
	}
	//cmd = malloc(sizeof(t_command));
	print_token(tokens);
	return;
}