#ifndef AST_STRUCT_H
# define AST_STRUCT_H

// enum pour preciser si < ou >
typedef enum e_redirection_type {
	REDIRECTION_IN,
	REDIRECTION_OUT,
} t_redirection_type;

//sous structure pour les redirection
typedef struct s_redirection {
    t_redirection_type type;
    char *target;                    // Fichier ou délimiteur
    struct s_redirection *next;      // Pour chaîner plusieurs redirections
} t_redirection;

//enum pour preciser le type du node de l'ast
typedef enum e_ast_type {
	AST_COMMAND,      // Commande simple
	AST_PIPE,         // Pipe
	AST_LOGICAL,      // && ou ||
	AST_SUBSHELL      // Expression entre ( ... ), exécutée dans un fork()
} t_ast_type;

//enum pour preciser si AST_LOGICAL est  && ou ||
typedef enum e_logical_type {
	LOGICAL_AND,
	LOGICAL_OR
} t_logical_type;

// structure de base de l'ast
typedef struct s_node {
    t_ast_type type;				// enum pour labeliser le type de node
    char **args;					// Tableau d'arguments de la commande
	t_logical_type logic_type;		// en cas de type AST_LOGICAL presise si && ou ||
    t_redirection *redirections;	// Liste des redirections associées à cette commande
    struct s_node *child;			// (Left) Premier enfant (pour des sous-commandes ou pipelines)
    struct s_node *brother;			// (Right) Frère suivant (pour chaîner des commandes au même niveau)
} t_node;

#endif