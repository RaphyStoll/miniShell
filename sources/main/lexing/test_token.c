/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:03:44 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/13 13:56:32 by Charlye          ###   ########.fr       */
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

void	test_handle_operator(void)
{
	t_token		*token_list;
	const char	*input1 = "|| test";
	const char	*input2 = "(";

	printf("\n Test handle_operator : \n");
	if (handle_operator(&token_list, &input1))
		printf("Token added : %s (expected ||)\n", token_list->str);
	else
		printf("Error, token not added\n");
	if (handle_operator(&token_list, &input2))
		printf("Token added : %s (expected ()\n", token_list->str);
	else
		printf("Error, token not added\n");
}

void	test_tokenizing(void)
{
	t_token		*token;
	const char	*input = "echo hello | cat || grep test > file.txt";

	token = tokenizing(input);
	printf("\nTest tokenizing :\n");
	while (token)
	{
		printf("Token : %s (Type : %d)\n", token->str, token->type);
		token = token->next;
	}
}

void	test_check_unclosed_quotes(void)
{
    printf("Testing check_unclosed_quotes:\n");
    check_unclosed_quotes("echo \"Hello");
    check_unclosed_quotes("ls -l '");
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
	test_is_parenthesis();
	test_is_operator();
	test_add_operator();
	test_handle_operator();
	test_tokenizing();
	test_check_unclosed_quotes();
	test_check_unclosed_parentheses();
	return (0);
}
