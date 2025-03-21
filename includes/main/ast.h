#ifndef AST_H
# define AST_H
# include "colors.h"
# include "lexing.h"



//sous structure pour les redirection
typedef struct s_redirection {
    t_type type;
    char *target;                    // Fichier ou délimiteur
    struct s_redirection *next;      // Pour chaîner plusieurs redirections
} t_redirection;

// structure de base de l'ast
typedef struct s_node {
    t_type type;                   // Par exemple : CMD, PIPE, LOGICAL, etc.
    char **args;                   // Tableau d'arguments de la commande
    struct s_node *child;          // (Left) Premier enfant (pour des sous-commandes ou pipelines)
    struct s_node *brother;        // (Right) Frère suivant (pour chaîner des commandes au même niveau)
    t_redirection *redirections;   // Liste des redirections associées à cette commande
} t_node;

//! utils
t_node *create_node(t_type type, char **args);
void add_child(t_node *parent, t_node *child);
void add_brother(t_node *node, t_node *brother);
void add_redirection(t_node *cmd, t_redirection *redir);

//! debbug
void print_ast(t_node *node, int indent);

#endif