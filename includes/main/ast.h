#ifndef AST_H
# define AST_H
# include "colors.h"
# include "lexing.h"

// enum pour l'ast
typedef enum e_node_type {
	AST_COMMAND,  // nœud représentant une commande simple avec ses arguments et redirections
	AST_PIPE,     // nœud représentant un pipeline
	AST_LOGICAL,  // nœud pour les opérateurs logiques (&&, ||)
	AST_GROUP     // nœud pour une expression entre parenthèses
} t_node_type;


//sous structure pour les redirection
typedef struct s_redirection {
    t_node_type type;
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

//!ast test
t_node *create_node(t_node_type type);
t_token *lex_input(char *input);
t_node *ast_from_tokens(t_token *tokens);
void print_ast_node(t_node *node, int indent);
void print_redirections(t_redirection *redir, int indent);
void print_ast(t_node *node, int indent);
void free_redirections(t_redirection *redir);
void free_ast(t_node *node);
int main(int argc, char **argv);

#endif