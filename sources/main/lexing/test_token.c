/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:03:44 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/13 15:59:23 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/lexing.h"

void	test_is_parenthesis(void)
{
	printf("Test is a parenthesis : \n");
	printf("( -> %d (expecting 1)\n", is_parenthesis('('));
	printf(") -> %d (expecting 1)\n", is_parenthesis(')'));
	printf("a -> %d (expecting 0)\n", is_parenthesis('a'));
	printf("{ -> %d (expecting 0)\n", is_parenthesis('{'));
}

void	test_is_operator(void)
{
	printf("Test is an operator : \n");
	printf(">> -> %d (expecting APPEND)\n", is_operator(">>"));
	printf("<< -> %d (expecting HEREDOC)\n", is_operator("<<"));
	printf("&& -> %d (expecting AND)\n", is_operator("&&"));
	printf("|| -> %d (expecting OR)\n", is_operator("||"));
	printf("| -> %d (expecting PIPE)\n", is_operator("|"));
	printf("< -> %d (expecting REDIRECT_IN)\n", is_operator("<"));
	printf("> -> %d (expecting REDIRECT_OUT)\n", is_operator(">"));
	printf("abc -> %d (expecting WORD)\n", is_operator("abc"));
}

void	test_handle_operator(void)
{
	t_token		*token_list;
	const char	*input1 = "|| test";
	const char	*input2 = "(";
	t_token		*last_token;

	token_list = NULL;  // ✅ Initialisation correcte

	printf("\n Test handle_operator : \n");

	// Test avec "||"
	if (handle_operator(&token_list, &input1))
	{
		// 🔍 Aller jusqu'au dernier token ajouté
		last_token = token_list;
		while (last_token->next)
			last_token = last_token->next;
		printf("Token added : %s (expected ||)\n", last_token->str);
	}
	else
		printf("Error, token not added\n");

	// Test avec "("
	if (handle_operator(&token_list, &input2))
	{
		// 🔍 Aller jusqu'au dernier token ajouté
		last_token = token_list;
		while (last_token->next)
			last_token = last_token->next;
		printf("Token added : %s (expected ()\n", last_token->str);
	}
	else
		printf("Error, token not added\n");

	// ✅ Libération mémoire après test
	free_all(token_list);
}


void	test_add_operator(void)
{
	t_token		*token_list;
	const char	*input = ">>abc";

	token_list = NULL;
	printf("Test add_operator : \n");
	if (add_operator(&token_list, &input, APPEND))
		printf("Added token : %s (expected >>)\n", token_list->str);
	else
		(printf("Error, token not added"));
	printf("New positon of input : %s (expected abc)\n", input);
}

void	test_tokenizing(void)
{
    t_token *tokens;
    
    const char *test_cases[] = {
        "echo hello && ls",            // ✅ Cas normal, opérateur séparé
        "echo hello&&ls",              // ✅ Opérateur collé, doit être séparé
        "echo 'hello && ls'",          // ✅ && à l'intérieur de quotes, ne doit pas être séparé
        "echo \"hello&&ls\"",          // ✅ Même test mais avec double quotes
        "echo \"hello\"&&ls",          // ✅ Quotes fermées avant &&
        "echo hello >file",            // ✅ Redirection sans espace
        "echo hello>file",             // ✅ Même test, doit être interprété pareil
        "(echo hello) && ls",          // ✅ Parenthèses + opérateurs
        "echo \"hello && ls",          // ❌ Quote non fermée, devrait renvoyer une erreur
        "echo hello && (ls",           // ❌ Parenthèse non fermée, devrait renvoyer une erreur
        NULL
    };

    printf("\n🟡 Running test_tokenizing() with various inputs...\n");

    for (int i = 0; test_cases[i] != NULL; i++)
    {
        printf("\n🟣 Test case %d: \"%s\"\n", i + 1, test_cases[i]);
        tokens = tokenizing(test_cases[i]);

        if (!tokens)
        {
            printf("❌ Tokenizing failed (expected for syntax errors)\n");
            continue;
        }

        printf("✅ Tokenizing successful, printing tokens:\n");
        t_token *tmp = tokens;
        while (tmp)
        {
            printf("🔹 Token: \"%s\" (Type: %d)\n", tmp->str, tmp->type);
            tmp = tmp->next;
        }
        free_all(tokens); // ✅ Libération de la mémoire
    }

    printf("🟢 All test cases processed!\n");
}


void	test_check_unclosed_quotes(void)
{
    printf("Testing check_unclosed_quotes:\n");
    check_unclosed_quotes("echo \"Hello");
    check_unclosed_quotes("ls -l '");
	check_unclosed_quotes("'text' \text\"");
    check_unclosed_quotes("'text' \"text\"");
}

void	test_check_unclosed_parentheses(void)
{
    printf("Testing check_unclosed_parentheses:\n");
    check_unclosed_parentheses("echo (ls | grep");
    check_unclosed_parentheses(")");
    check_unclosed_parentheses("(ls | grep)");
}

int	main(void)
{
	//test_is_parenthesis();
	//test_is_operator();
	//test_handle_operator();
	//test_add_operator();
	//test_check_unclosed_parentheses();
	//test_check_unclosed_quotes();
	test_tokenizing();
	return (0);
}
