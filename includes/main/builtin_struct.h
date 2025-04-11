/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 12:39:05 by raphaelferr       #+#    #+#             */
/*   Updated: 2025/04/11 11:34:16 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_STRUCT_H
# define BUILTIN_STRUCT_H

// prend une structure pour permettre de prendre en compte d'autres argument
//? (pas speciallement utile dans minishell)
//! ajouter bool x pour l'option prise en compte (bool e = echo -e)
typedef struct s_echo_opts
{
	bool	n;
}	t_echo_opts;

#endif
