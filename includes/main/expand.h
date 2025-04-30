/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:51:34 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/30 18:22:45 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "env_struct.h"
# include "ast_struct.h"
# include <stdlib.h>
# include <dirent.h>

bool	expand_all(t_node *node, t_shell *shell);
bool	expand_redirections(t_node *node, t_shell *shell);
char	*expand_one_arg(char *arg, t_shell *shell);
bool	handle_variable(char **result, char *arg, int *i, t_shell *shell);
bool	handle_regular_char(char **result, char c);
bool	handle_exit_status(char **result, t_shell *shell);
bool	remove_empty_args(t_node *node);

/* expand wildcard*/
bool	expand_wildcard(t_node *node);
bool	contains_wildcard(char *arg);
bool	expand_single_wildcard_arg(t_node *node, int *index);
int		count_matches(char *arg);
bool	wildcard_match(char *arg, char *name);
void	handle_star(int *i, int *j, int *star_idx, int *name_idx);
void	handle_memory(int *i, int *j, int *star_idx, int *name_idx);
char	**collect_matches(char *arg, int count);
int		fill_matches(DIR *dir, char **matches, int *ptr_j, char *arg);
void	sort_args_lexico(char **array, int count);
void	replace_args_in_list(t_node *node, int i, char **matches, int count);
char	**allocate_new_args(int nb_args, int count);
int		calculate_nb_args(t_node *node);
void	copy_new_args(char **matches, char **new_args, int *dst, int count);

#endif
