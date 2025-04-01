#ifndef ECHO_STRUCT_H
#define ECHO_STRUCT_H

// prend une structure pour permettre de prendre en compte d'autres argument
//? (pas speciallement utile dans minishell)
//! ajouter bool x pour l'option prise en compte (bool e = echo -e)
typedef struct s_echo_opts
{
	bool	n;
}	t_echo_opts;

#endif