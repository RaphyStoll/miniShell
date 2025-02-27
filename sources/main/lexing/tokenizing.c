/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 14:59:03 by chpasqui          #+#    #+#             */
/*   Updated: 2025/02/27 17:00:10 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"

bool is_separator(char c)
{
	return (c == '|' || c == '<' || c == '>c');
}

bool is_special_operator(const char *input)
{
	return ((!ft_strncmp(input, ">>", 2) || (!ft_strncmp(input, "<<", 2)
			!ft_strncmp(input, "&&", 2) || !ft_strncmp(input, "||", 2));
}

// Split input into a list of raw tokens
t_token	*tokenizing(const char *input)
{
	t_token	*token_list;

	token_list = NULL;
	while (*input)
	{
		if (*input == ' ')
			input++;
		else if (is_special_operator(input))
			add_token(&token_list, handle_separator(&input));
		else if (is_separator(input))
			add_token(&token_list, handle_separator(&input));
		else
			add_token(&token_list, handle_word(&input));
	}
	return (token_list);
}

bool handle_separators(t_token **token_list, const char **input)
{
    int op
	
	op = is_special_operator(*input);
    if (!op)
        return (false);
    if (op == REDIRECT_IN && !add_token(token_list, (ft_strdup("<"), REDIRECT_IN)))
        return (false);
    else if (op == HEREDOC && !add_token(token_list,(ft_strdup("<<"), HEREDOC)))
        return (false);
    else if (op == REDIRECT_OUT && !add_token(token_list,(ft_strdup(">"), REDIRECT_OUT)))
        return (false);
    else if (op == APPEND && !add_token(token_list,ft_strdup(">>"), APPEND))
        return (false);
    else if (op == PIPE && !add_token(token_list, ft_strdup("|"), PIPE))
        return (false);
    else if (op == OR && !add_token(token_list,(ft_strdup("||"), OR)))
        return (false);
    else if (op == AND && !add_token(token_list,(ft_strdup("&&"), AND)))
        return (false);
    else if (op == O_PARENTHESIS && !add_token(token_list,(ft_strdup("("), O_PARENTHESIS)))
        return (false);
    else if (op == C_PARENTHESIS && !add_token(token_list,(ft_strdup(")"), C_PARENTHESIS)))
        return (false);
    if (op == REDIRECT_IN || op == REDIRECT_OUT || op == PIPE || op == O_PARENTHESIS || op == C_PARENTHESIS)
        (*input)++;
    else if (op == HEREDOC || op == APPEND || op == OR || op == AND)
        (*input) += 2;
    return (true);
}
