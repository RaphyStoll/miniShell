#include "../../../includes/main/error_code.h"
#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"


void print_tokken(t_token *tokens)
{
	
	printf("Parsing tokens:\n");
    while (tokens != NULL) {
        printf("Token: %s, Type: %d\n", tokens->str, tokens->type);
        tokens = tokens->next;
    }
}

void nbr_error(t_error error_code, char *message) {
		perror(RED BOLD"Error"NC);
	printf(YELLOW"%s\n"NC, message);
	(void)error_code;
}