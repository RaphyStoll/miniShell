/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:43 by raphalme          #+#    #+#             */
/*   Updated: 2025/04/01 19:31:16 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "error_code.h"
# include "env_struct.h"
# include "ast_struct.h"
# include "../../lib/libft/header/libft.h"
# include "../../lib/libft/header/libft_bonus.h"

typedef struct s_shell
{
	t_env		*env;          // Variables d'environnement (liées à export/unset/env)
	t_node		*ast;          // Arbre de commandes
	int			last_exit;     // Valeur de $? utilisée partout
}	t_shell;git 


//int	main(int argc, char **argv, char **envp);

#endif