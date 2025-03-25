/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 15:43:43 by raphalme          #+#    #+#             */
/*   Updated: 2025/03/25 12:09:34 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../../includes/main/lexing.h"
# include "../../includes/main/parsing.h"
# include "../../includes/main/error_code.h"
# include "../../includes/main/signals.h"
# include <readline/readline.h>
# include <readline/history.h>

# include "error_code.h"
# include "lexing.h"
# include "parsing.h"
# include "utils.h"

int main(void);

#endif