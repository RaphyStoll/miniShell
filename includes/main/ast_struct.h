/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raphaelferreira <raphaelferreira@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:48:16 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/03/25 20:07:35 by raphaelferr      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_STRUCT_H
# define AST_STRUCT_H

/**
 * @brief Enum pour type de redirection
 * @param REDIRECTION_IN = <
 * @param REDIRECTION_OUT = >
 * @param REDIRECTION_APPEND = >>
 * @param REDIRECTION_HEREDOC = <<
 */
typedef enum e_redirection_type
{
	REDIRECTION_IN,
	REDIRECTION_OUT,
	REDIRECTION_APPEND,
	REDIRECTION_HEREDOC
}	t_redirection_type;

/**
 * @brief struct pour gerer les redirection en cas d'AST_COMMAND
 * @param type pointe vers t_redirection_type
 * @param target fichier ou delimiteur
 * @param next chaine plusieur redirection
 */
typedef struct s_redirection
{
	t_redirection_type		type;
	char					*target;
	struct s_redirection	*next;
}	t_redirection;

/**
 * @brief Enum pout les type de node de l'authors
 * @param AST_COMMAND commande simple
 * @param AST_PIPE pipe
 * @param AST_LOGICAL operateur logique (&& ou ||)
 * @param AST_SUBSHELL subshell d'expression (...)
 */
typedef enum e_ast_type
{
	AST_COMMAND,
	AST_PIPE,
	AST_LOGICAL,
	AST_SUBSHELL
}	t_ast_type;

/**
 * @brief enum pour definir l'operateur en cas de AST_LOGICAL
 * @param LOGICAL_AND &&
 * @param LOGICAL_OR ||
 */
typedef enum e_logical_type
{
	LOGICAL_AND,
	LOGICAL_OR
}	t_logical_type;

/**
 * @brief Structure for AST nodes.
 * @param type vers enum ast_type pour definir le type de node
 * @param args tableau d'argument en cas de AST_COMMAND ex: ("ls", "-l", "-a")
 * @param redirection lise chainer de t_redirection en cas de AST_COMMMAND
 * @param child pointe vers l'enfant du noeu actuel (left)
 * @param brother pointe vers le noeu de meme niveau que l'actuel (right)
 */
typedef struct s_node
{
	t_ast_type		type;
	char			**args;
	t_logical_type	logic_type;
	t_redirection	*redirections;
	struct s_node	*child;
	struct s_node	*brother;
}	t_node;

#endif