#include "../../../includes/main/parsing.h"

// Fonction pour créer un nouveau token
t_token *create_token(char *str, t_token_type type) {
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    new_token->str = strdup(str);
    new_token->type = type;
    new_token->prev = NULL;
    new_token->next = NULL;
    return new_token;
}

// Fonction de tokenisation simple
t_token *tokenize(char *input) {
    t_token *head = NULL;
    t_token *current = NULL;
    char *token = strtok(input, " \t\n");

    while (token != NULL) {
        t_token *new_token = create_token(token, WORD);
        if (head == NULL) {
            head = new_token;
            current = new_token;
        } else {
            current->next = new_token;
            new_token->prev = current;
            current = new_token;
        }
        token = strtok(NULL, " \t\n");
    }
    return head;
}

// Fonction principale pour lire et parser les commandes
void read_and_parse() {
    char *input;
    while ((input = readline("minishell> ")) != NULL) {
        if (*input != '\0') {
            t_token *tokens = tokenize(input);
            printf("Parsing tokens:\n");
    while (tokens != NULL) {
        printf("Token: %s, Type: %d\n", tokens->str, tokens->type);
        tokens = tokens->next;
    }
			print_tokken(tokens);
			//init_parsing(tokens);

            // Libérer la mémoire allouée pour les tokens
            t_token *current = tokens;
            while (current != NULL) {
                t_token *temp = current;
                current = current->next;
                free(temp->str);
                free(temp);
            }
        }
        free(input);
    }
}

int main() {
    read_and_parse();
    return 0;
}
