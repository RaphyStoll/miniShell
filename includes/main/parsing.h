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

//enum pour les redirection (use dans s_redirection)
typedef enum e_redir_type {
    REDIR_IN,     // <
    REDIR_OUT,    // >
    REDIR_APPEND, // >>
    HEREDOC       // <<
} t_redir_type;

// enum pour l'ast
typedef enum e_node_type {
	AST_COMMAND,  // nœud représentant une commande simple avec ses arguments et redirections
	AST_PIPE,     // nœud représentant un pipeline
	AST_LOGICAL,  // nœud pour les opérateurs logiques (&&, ||)
	AST_GROUP     // nœud pour une expression entre parenthèses
} t_node_type;


//sous structure pour les redirection
typedef struct s_redirection {
    t_redir_type type;
    char *target;                    // Fichier ou délimiteur
    struct s_redirection *next;      // Pour chaîner plusieurs redirections
} t_redirection;

// structure de base de l'ast
typedef struct s_node {
    enum e_node_type type;         // Par exemple : CMD, PIPE, LOGICAL, etc.
    char **args;                   // Tableau d'arguments de la commande
    struct s_node *child;          // Premier enfant (pour des sous-commandes ou pipelines)
    struct s_node *brother;        // Frère suivant (pour chaîner des commandes au même niveau)
    t_redirection *redirections;   // Liste des redirections associées à cette commande
} t_node;

//!parsing
bool	init_parsing(t_token *tokens);

//!test
int	parse_tokens(t_token *head);
t_token	*create_token(char *str, t_type type);
void	add_token(t_token **head, t_token *new_token);
t_token	*create_test_case_1(void);
t_token	*create_test_case_2(void);
t_token	*create_test_case_3(void);
t_token	*create_test_case_4(void);
t_token	*create_test_case_5(void);
int	main(int argc, char **argv);

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
bool handle_redirection_exceptions(t_token *token_list);

//!error
void	ft_exit_error(t_token *token, char *message, t_error error_code);
void	nbr_error(t_error error_code, char *message);

//!free
void	free_tokens(t_token *head);
void	free_all(t_token *token);

#endif