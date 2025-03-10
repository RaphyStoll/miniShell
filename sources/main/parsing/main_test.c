#include "../../../includes/main/parsing.h"

// Fonction pour créer un nouveau token
t_token	*create_token(char *str, t_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = strdup(str);
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

// Fonction pour ajouter un token à la fin de la liste
void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (*head == NULL)
	{
		*head = new_token;
		return;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

// Fonction qui simule ton parsing (à remplacer par ta vraie fonction)
int	parse_tokens(t_token *head)
{
	int res = init_parsing(head);
	return (res);
}

// Fonction pour créer des chaînes de test prédéfinies
t_token	*create_test_case_1(void)
{
	// Test case: ls -la | grep .c > output.txt
	t_token	*head = NULL;

	add_token(&head, create_token("ls", WORD));
	add_token(&head, create_token("-la", WORD));
	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("grep", WORD));
	add_token(&head, create_token(".c", WORD));
	add_token(&head, create_token(">", REDIRECT_OUT));
	add_token(&head, create_token("output.txt", WORD));
	return (head);
}

t_token	*create_test_case_2(void)
{
	// Test case: cat < input.txt | sort | uniq >> result.txt
	t_token	*head = NULL;

	add_token(&head, create_token("cat", WORD));
	add_token(&head, create_token("<", REDIRECT_IN));
	add_token(&head, create_token("input.txt", WORD));
	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("sort", WORD));
	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("uniq", WORD));
	add_token(&head, create_token(">>", APPEND));
	add_token(&head, create_token("result.txt", WORD));
	return (head);
}

t_token	*create_test_case_3(void)
{
	// Test case: (echo hello && ls) || (cat file && grep pattern)
	t_token	*head = NULL;

	add_token(&head, create_token("(", O_PARENTHESIS));
	add_token(&head, create_token("echo", WORD));
	add_token(&head, create_token("hello", WORD));
	add_token(&head, create_token("&&", AND));
	add_token(&head, create_token("ls", WORD));
	add_token(&head, create_token(")", C_PARENTHESIS));
	add_token(&head, create_token("||", OR));
	add_token(&head, create_token("(", O_PARENTHESIS));
	add_token(&head, create_token("cat", WORD));
	add_token(&head, create_token("file", WORD));
	add_token(&head, create_token("&&", AND));
	add_token(&head, create_token("grep", WORD));
	add_token(&head, create_token("pattern", WORD));
	add_token(&head, create_token(")", C_PARENTHESIS));
	return (head);
}

t_token	*create_test_case_4(void)
{
	// Test case: cat << EOF | wc -l
	t_token	*head = NULL;

	add_token(&head, create_token("cat", WORD));
	add_token(&head, create_token("<<", HEREDOC));
	add_token(&head, create_token("EOF", WORD));
	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("wc", WORD));
	add_token(&head, create_token("-l", WORD));
	return (head);
}

t_token	*create_test_case_5(void)
{
	// Test case: echo "Bonjour $USER"
	t_token	*head = NULL;

	add_token(&head, create_token("echo", WORD));
	add_token(&head, create_token("Bonjour $USER", WORD)); // Supposé être traité comme un seul token avec variable
	return (head);
}

// CAS D'ERREURS

t_token	*create_error_case_1(void)
{
	// Erreur: | ls
	// Commande commençant par un pipe
	t_token	*head = NULL;

	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("ls", WORD));
	return (head);
}

t_token	*create_error_case_2(void)
{
	// Erreur: ls | | grep
	// Pipes consécutifs
	t_token	*head = NULL;

	add_token(&head, create_token("ls", WORD));
	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("grep", WORD));
	return (head);
}

t_token	*create_error_case_3(void)
{
	// Erreur: ls >
	// Redirection sans fichier
	t_token	*head = NULL;

	add_token(&head, create_token("ls", WORD));
	add_token(&head, create_token(">", REDIRECT_OUT));
	return (head);
}

t_token	*create_error_case_4(void)
{
	// Erreur: (ls
	// Parenthèses non fermées
	t_token	*head = NULL;

	add_token(&head, create_token("(", O_PARENTHESIS));
	add_token(&head, create_token("ls", WORD));
	return (head);
}

t_token	*create_error_case_5(void)
{
	// Erreur: ls)
	// Parenthèse fermante sans ouvrante
	t_token	*head = NULL;

	add_token(&head, create_token("ls", WORD));
	add_token(&head, create_token(")", C_PARENTHESIS));
	return (head);
}

t_token	*create_error_case_6(void)
{
	// Erreur: ls | && cat
	// Opérateurs logiques mal placés
	t_token	*head = NULL;

	add_token(&head, create_token("ls", WORD));
	add_token(&head, create_token("|", PIPE));
	add_token(&head, create_token("&&", AND));
	add_token(&head, create_token("cat", WORD));
	return (head);
}

t_token	*create_error_case_7(void)
{
	// Erreur: cat << 
	// Heredoc sans délimiteur
	t_token	*head = NULL;

	add_token(&head, create_token("cat", WORD));
	add_token(&head, create_token("<<", HEREDOC));
	return (head);
}

t_token	*create_error_case_8(void)
{
	// Erreur: (echo hello) && (ls
	// Deuxième paire de parenthèses non fermée
	t_token	*head = NULL;

	add_token(&head, create_token("(", O_PARENTHESIS));
	add_token(&head, create_token("echo", WORD));
	add_token(&head, create_token("hello", WORD));
	add_token(&head, create_token(")", C_PARENTHESIS));
	add_token(&head, create_token("&&", AND));
	add_token(&head, create_token("(", O_PARENTHESIS));
	add_token(&head, create_token("ls", WORD));
	return (head);
}

t_token	*create_error_case_9(void)
{
	// Erreur: || ls
	// Commande commençant par un opérateur logique
	t_token	*head = NULL;

	add_token(&head, create_token("||", OR));
	add_token(&head, create_token("ls", WORD));
	return (head);
}

t_token	*create_error_case_10(void)
{
	// Erreur: ls |
	// Pipe à la fin sans commande qui suit
	t_token	*head = NULL;

	add_token(&head, create_token("ls", WORD));
	add_token(&head, create_token("|", PIPE));
	return (head);
}


int	main(void)
{
	t_token	*tokens;
	int		choice;
	int		result;

	printf("Choisissez un cas de test (1-15):\n");
	printf("1-5: Cas valides\n");
	printf("6-15: Cas d'erreurs\n");
	printf("Choix: ");
	scanf("%d", &choice);

	switch (choice)
	{
		// Cas valides
		case 1:
			tokens = create_test_case_1();
			printf("Test: ls -la | grep .c > output.txt\n");
			break;
		case 2:
			tokens = create_test_case_2();
			printf("Test: cat < input.txt | sort | uniq >> result.txt\n");
			break;
		case 3:
			tokens = create_test_case_3();
			printf("Test: (echo hello && ls) || (cat file && grep pattern)\n");
			break;
		case 4:
			tokens = create_test_case_4();
			printf("Test: cat << EOF | wc -l\n");
			break;
		case 5:
			tokens = create_test_case_5();
			printf("Test: echo \"Bonjour $USER\"\n");
			break;
		
		// Cas d'erreurs
		case 6:
			tokens = create_error_case_1();
			printf("Test ERREUR: | ls (commande commençant par un pipe)\n");
			break;
		case 7:
			tokens = create_error_case_2();
			printf("Test ERREUR: ls | | grep (pipes consécutifs)\n");
			break;
		case 8:
			tokens = create_error_case_3();
			printf("Test ERREUR: ls > (redirection sans fichier)\n");
			break;
		case 9:
			tokens = create_error_case_4();
			printf("Test ERREUR: (ls (parenthèse non fermée)\n");
			break;
		case 10:
			tokens = create_error_case_5();
			printf("Test ERREUR: ls) (parenthèse fermante sans ouvrante)\n");
			break;
		case 11:
			tokens = create_error_case_6();
			printf("Test ERREUR: ls | && cat (opérateurs logiques mal placés)\n");
			break;
		case 12:
			tokens = create_error_case_7();
			printf("Test ERREUR: cat << (heredoc sans délimiteur)\n");
			break;
		case 13:
			tokens = create_error_case_8();
			printf("Test ERREUR: (echo hello) && (ls (deuxième parenthèse non fermée)\n");
			break;
		case 14:
			tokens = create_error_case_9();
			printf("Test ERREUR: || ls (commande commençant par un opérateur logique)\n");
			break;
		case 15:
			tokens = create_error_case_10();
			printf("Test ERREUR: ls | (pipe à la fin sans commande qui suit)\n");
			break;
		default:
			printf("Choix invalide, utilisation du test 1 par défaut\n");
			tokens = create_test_case_1();
			printf("Test: ls -la | grep .c > output.txt\n");
	}

	print_tokens(tokens);
	
	result = parse_tokens(tokens);
	if (choice >= 6 && choice <= 15)
	{
		if (result != 0)
			printf("✅ Erreur correctement détectée! (Code retour: %d)\n", result);
		else
			printf("❌ L'erreur n'a PAS été détectée! Le parser a retourné 0\n");
	}
	else
	{
		if (result == 0)
			printf("✅ Commande valide correctement analysée! (Code retour: %d)\n", result);
		else
			printf("❌ Erreur incorrectement signalée! Le parser a retourné %d\n", result);
	}
	
	free_tokens(tokens);
	return (0);
}

