/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:32:42 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/10 17:59:31 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/main/parsing.h"

// Fonction d'initialisation du parsing (à implémenter)
bool init_parsing(t_token *tokens) {
	//t_command *cmd;
	
	if (if_valide_token(tokens))
	{
		printf("tokken error\n");
		return 1;
	}
	printf(BLUE BOLD"tokken is ok\n"NC);
	//cmd = malloc(sizeof(t_command));
	return 0;
}