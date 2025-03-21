#ifndef AST_H
# define AST_H
# include "colors.h"
# include "lexing.h"
# include <stdlib.h>
# include "ast_struct.h"

//! utils
//t_node *create_node(t_type type, char **args);
void add_child(t_node *parent, t_node *child);
void add_brother(t_node *node, t_node *brother);
void add_redirection(t_node *cmd, t_redirection *redir);

//! parse
t_node *parse_command(t_token **tokens);

//! debbug
void print_ast(t_node *node, int indent);

#endif