/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:43 by raphalme          #+#    #+#             */
/*   Updated: 2025/04/24 12:13:59 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define SHELL_NAME "Minishell : "
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "error_code.h"
# include "env_struct.h"
# include "ast_struct.h"
# include "signals.h"
# include "../../lib/libft/header/libft.h"
# include "../../lib/libft/header/libft_bonus.h"

typedef struct s_shell
{
	t_env		*env;
	t_node		*ast;
	int			last_exit_status;
	char		*prompt;
	int			shell_level;
}	t_shell;

//int	main(int argc, char **argv, char **envp);
bool	init_shell_level(t_shell *shell);

#endif