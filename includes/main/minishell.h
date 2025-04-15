/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:43 by raphalme          #+#    #+#             */
/*   Updated: 2025/04/15 17:57:10 by raphaelferr      ###   ########.fr       */
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
# include "signals.h"
# include "../../lib/libft/header/libft.h"
# include "../../lib/libft/header/libft_bonus.h"

typedef struct s_shell
{
	t_env		*env;
	t_node		*ast;
	int			last_exit_status;
	char		*prompt;
}	t_shell;

//int	main(int argc, char **argv, char **envp);

#endif