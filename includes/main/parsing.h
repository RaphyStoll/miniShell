/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 14:35:57 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/20 15:08:15 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "error_code.h"
# include "colors.h"
# include "lexing.h"
# include "../../lib/libft/header/libft.h"
# include "../../lib/libft/header/libft_bonus.h"

//structure pour la partie parsing exemple ci dessous
//? ex: ls -l -a
// name = ls
// argument = [0]-l [1]-a
// argument_count = 2
// input = NULL 
// output = NULL 

//!parsing
bool	init_parsing(t_token *tokens);

//!test
int		parse_tokens(t_token *head);
t_token	*create_token(char *str, t_type type);

//void	add_token(t_token **head, t_token *new_token);
t_token	*create_test_case_1(void);
t_token	*create_test_case_2(void);
t_token	*create_test_case_3(void);
t_token	*create_test_case_4(void);
t_token	*create_test_case_5(void);
int		main(int argc, char **argv);

//! debbug
void	print_tokens(t_token *head);
void	print_tab(char **tab);
void	print_node(t_token *current);
void	print_list(t_token **head);
void	print_current_token(t_token *token);


//!token verif
bool	if_valide_token_prev(t_token *current);
bool	if_valide_token_next(t_token *current);
bool	valid_content(t_token *current);

//! verif pipe and word
bool	valid_type_pipe_prev(t_token *cur);
bool	valid_type_pipe_next(t_token *cur);
bool	valid_type_word_prev(t_token *cur);
bool	valid_type_word_next(t_token *cur);

//! verif redirect
bool	valid_type_redirect_in_prev(t_token *cur);
bool	valid_type_redirect_in_next(t_token *cur);
bool	valid_type_redirect_out_prev(t_token *cur);
bool	valid_type_redirect_out_next(t_token *cur);

//! verif And / or
bool	valid_type_and_prev(t_token *cur);
bool	valid_type_and_next(t_token *cur);
bool	valid_type_or_prev(t_token *cur);
bool	valid_type_or_next(t_token *cur);

//! verif heredoc et append
bool	valid_type_heredoc_prev(t_token *cur);
bool	valid_type_heredoc_next(t_token *cur);
bool	valid_type_append_prev(t_token *cur);
bool	valid_type_append_next(t_token *cur);

//! verif exception
bool	handle_redirection_exceptions(t_token *token_list);

//!error
void	ft_exit_error(t_token *token, char *message, t_error error_code);
void	nbr_error(t_error error_code, char *message);

//!free
void	free_tokens(t_token *head);
void	free_all(t_token *token);

#endif