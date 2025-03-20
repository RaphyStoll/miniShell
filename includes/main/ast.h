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


//! utils
t_node *create_node(t_node_type type, char **args);
void add_child(t_node *parent, t_node *child);
void add_brother(t_node *node, t_node *brother);
void add_redirection(t_node *cmd, t_redirection *redir);

#endif