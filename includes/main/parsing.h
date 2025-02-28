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
void print_tokken(t_token *tokens);
void nbr_error(t_error error_code, char *message);


//!error
void	ft_exit_error(t_token *token, char *message, t_error error_code);

//!free
void free_all(t_token *token);

#endif