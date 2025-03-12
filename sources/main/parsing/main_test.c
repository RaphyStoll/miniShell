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
	//printf("res = %d", res);
		return res;
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

// Cas impossibles ou types inexistants

t_token	*create_error_case_11(void)
{
	// Erreur: token avec un type invalide
	t_token	*head = NULL;

	t_token *invalid_token = create_token("invalid", 10);
	add_token(&head, invalid_token);
	return (head);
}

t_token	*create_error_case_12(void)
{
	// Erreur: commande avec redirection vide
	t_token	*head = NULL;

	add_token(&head, create_token("echo", WORD));
	add_token(&head, create_token("hello", WORD));
	add_token(&head, create_token(">", REDIRECT_OUT));
	add_token(&head, create_token("", WORD)); // Nom de fichier vide
	return (head);
}

t_token	*create_error_case_13(void)
{
	// Erreur: commande avec plusieurs redirections du même type consécutives
	t_token	*head = NULL;

	add_token(&head, create_token("cat", WORD));
	add_token(&head, create_token("<", REDIRECT_IN));
	add_token(&head, create_token("<", REDIRECT_IN)); // Double redirection
	add_token(&head, create_token("file.txt", WORD));
	return (head);
}

t_token	*create_error_case_14(void)
{
	// Erreur: structure imbriquée incorrecte
	t_token	*head = NULL;

	add_token(&head, create_token("(", O_PARENTHESIS));
	add_token(&head, create_token("(", O_PARENTHESIS));
	add_token(&head, create_token("echo", WORD));
	add_token(&head, create_token("test", WORD));
	add_token(&head, create_token(")", C_PARENTHESIS));
	// Parenthèse manquante
	return (head);
}

t_token	*create_error_case_15(void)
{
	// Erreur: opérateurs logiques consécutifs
	t_token	*head = NULL;

	add_token(&head, create_token("echo", WORD));
	add_token(&head, create_token("test", WORD));
	add_token(&head, create_token("&&", AND));
	add_token(&head, create_token("||", OR)); // Opérateurs consécutifs
	add_token(&head, create_token("ls", WORD));
	return (head);
}

// Fonction pour analyser une chaîne unique et la diviser en tokens
t_token *parse_single_argument(char *arg)
{
	t_token *head = NULL;
	char *token;
	char *rest = arg;
	char *delimiters = " \t";
	
	// Utiliser strtok pour diviser la chaîne par espaces
	token = strtok(rest, delimiters);
	while (token != NULL)
	{
		t_type type = WORD; // Par défaut
		
		// Déterminer le type de token
		if (strcmp(token, "|") == 0)
			type = PIPE;
		else if (strcmp(token, ">") == 0)
			type = REDIRECT_OUT;
		else if (strcmp(token, "<") == 0)
			type = REDIRECT_IN;
		else if (strcmp(token, ">>") == 0)
			type = APPEND;
		else if (strcmp(token, "<<") == 0)
			type = HEREDOC;
		else if (strcmp(token, "&&") == 0)
			type = AND;
		else if (strcmp(token, "||") == 0)
			type = OR;
		else if (strcmp(token, "(") == 0)
			type = O_PARENTHESIS;
		else if (strcmp(token, ")") == 0)
			type = C_PARENTHESIS;
			
		// Créer et ajouter le token
		add_token(&head, create_token(token, type));
		
		// Passer au token suivant
		token = strtok(NULL, delimiters);
	}
	
	return head;
}

// Fonction pour afficher l'aide
void	display_help(void)
{
	printf("Usage: ./parser [OPTION]\n\n");
	printf("Options:\n");
	printf("  Sans argument       Mode interactif avec menu\n");
	printf("  [1-20]              Exécuter un cas de test prédéfini\n");
	printf("                      1-5: Commandes valides\n");
	printf("                      6-20: Commandes avec erreurs\n");
	printf("  \"tokens...\"         Créer une séquence de tokens personnalisée\n");
	printf("                      Exemple: ./parser \"ls -la | grep .c > output.txt\"\n");
	printf("  -h, --help          Afficher cette aide\n");
}

int	main(int argc, char **argv)
{
	t_token	*tokens = NULL;
	int		choice = 0;
	int		result;

	// Afficher l'aide si demandé
	if (argc > 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
	{
		display_help();
		return (0);
	}

	if (argc == 1)
	{
		// Mode interactif existant avec scanf
		printf("Choisissez un cas de test (1-20):\n");
		printf("1-5: Cas valides\n");
		printf("6-20: Cas d'erreurs\n");
		printf("Choix: ");
		scanf("%d", &choice);
	}
	else if (argc == 2)
	{
		// Essayer de convertir l'argument en nombre pour les cas prédéfinis
		choice = atoi(argv[1]);
		
		if (choice > 0 && choice <= 20)
		{
			// C'est un choix numérique valide, utiliser les cas prédéfinis
		}
		else
		{
			// Ce n'est pas un nombre entre 1 et 20, traiter comme une chaîne de tokens
			printf("Test personnalisé avec la commande: %s\n", argv[1]);
			tokens = parse_single_argument(argv[1]);
			
			// Aller directement à l'évaluation
			print_tokens(tokens);
			result = parse_tokens(tokens);
			
			// Afficher le résultat
			printf("Résultat du parsing: %d ", result);
			if (result == 0)
				printf("(Commande considérée comme valide)\n");
			else
				printf("(Erreur détectée)\n");
			
			free_tokens(tokens);
			return (0);
		}
	}
	else
	{
		printf("Erreur: trop d'arguments. Utilisez des guillemets pour encadrer la commande.\n");
		printf("Exemple: ./parser \"ls -la | grep .c\"\n");
		printf("Utilisez --help pour plus d'informations.\n");
		return (1);
	}

	// Code existant pour les cas prédéfinis
	switch (choice)
	{
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
		
		// Cas d'erreurs existants
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
			
		// Nouveaux cas d'erreurs
		case 16:
			tokens = create_error_case_11();
			printf("Test ERREUR: token avec un type invalide (999)\n");
			break;
		case 17:
			tokens = create_error_case_12();
			printf("Test ERREUR: echo hello > (redirection vers un fichier vide)\n");
			break;
		case 18:
			tokens = create_error_case_13();
			printf("Test ERREUR: cat < < file.txt (redirections multiples consécutives)\n");
			break;
		case 19:
			tokens = create_error_case_14();
			printf("Test ERREUR: ((echo test) (parenthèse imbriquée non fermée)\n");
			break;
		case 20:
			tokens = create_error_case_15();
			printf("Test ERREUR: echo test && || ls (opérateurs logiques consécutifs)\n");
			break;
		default:
			printf("Choix invalide, utilisation du test 1 par défaut\n");
			tokens = create_test_case_1();
			printf("Test: ls -la | grep .c > output.txt\n");
	}

	print_tokens(tokens);
	
	result = parse_tokens(tokens);
	if (choice >= 6 && choice <= 20)
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
