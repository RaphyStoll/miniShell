#ifndef PARSING_H
#define PARSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdbool.h>
#include "error_code.h"
#include "colors.h"
#include "lexing.h"
#include "../../lib/libft/header/libft.h"
#include "../../lib/libft/header/libft_bonus.h"

//structure pour la partie parsing exemple ci dessous
//? ex: ls -l -a
// name = ls
// argument = [0]-l [1]-a
// argument_count = 2
// input = NULL 
// output = NULL 
typedef struct s_command {
	char	*name;				// Nom de la commande 
	char	**arguments;		// Tableau des arguments de la commande
	int		argument_count;		// Nombre d'arguments
	char	*input_file;		// NULL ou = nom de fichier(pas path)
	char	*output_file;		// NULL ou = nom de fichier(pas path)
	struct	s_command *next;	// Pointeur vers la commande suivante (pour les pipes)
} t_command;

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


//!token verif
bool	if_valide_token(t_token *tokens);
bool	valid_content(t_token *current);

//! verif pipe and word
bool	valid_type_pipe(t_token *cur);
bool	valid_type_word(t_token *current);

//!error
void	ft_exit_error(t_token *token, char *message, t_error error_code);
void nbr_error(t_error error_code, char *message);

//!free
void free_all(t_token *token);

#endif