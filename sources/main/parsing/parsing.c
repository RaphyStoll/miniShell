/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/20 14:28:41 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

// Fonction d'initialisation du parsing (à implémenter)
bool init_parsing(t_token *tokens)
{
	//t_command *cmd;
	print_current_token(tokens);
	printf(CYAN"start init parsing\n"NC);
	if (!valid_content(tokens))
	{
		printf("valid content don't passed\n");
		return (1);
	}
	if (!(handle_redirection_exceptions(tokens)))
	{
		printf("exeptions passed\n");
		return 0;
	}
	if (!if_valide_token_prev(tokens))
	{
		printf("tokken prev error\n");
		return (1);
	}
	if (!if_valide_token_next(tokens))
	{
		printf("tokken next error\n");
		return (1);
	}
	printf(BLUE BOLD"tokken is ok\n"NC);
	//cmd = malloc(sizeof(t_command));
	return (0);
}
