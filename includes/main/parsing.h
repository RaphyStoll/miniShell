#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "error_code.h"
#include "colors.h"
#include "lexing.h"
#include "../../lib/libft/header/libft.h"
#include "../../lib/libft/header/libft_bonus.h"

typedef struct s_pars {
	t_token *tokken;
	int error_code;
} t_pars;

//!parsing
void init_parsing(t_token *tokens);

//!test
t_token *create_token(char *str, t_token_type type);
t_token *tokenize(char *input);
void read_and_parse();
int main();

//! debbug
void print_token(t_token *token);
void	print_tab(char **tab);
void	print_node(t_token *current);
void	print_list(t_token **head);


//!error
void	ft_exit_error(t_token *token, char *message, t_error error_code);
void nbr_error(t_error error_code, char *message);

//!free
void free_all(t_token *token);

#endif