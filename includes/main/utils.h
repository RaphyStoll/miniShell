/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:57:57 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/25 19:46:09 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <string.h>
# include <unistd.h>
# include "colors.h"
# include "lexing_struct.h"
# include "minishell.h"

// Error handling
void	nbr_error(t_error error_code, char *message);
t_token	*ft_exit_error(t_token *tokens, t_error code, char *error_token);
void	print_error_message(t_error code, char *error_token);

//Memory utils
void	free_all(t_token *token);
void	free_tokens(t_token *head);

#endif