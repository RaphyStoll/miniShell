/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 09:16:23 by Charlye           #+#    #+#             */
/*   Updated: 2025/04/12 18:32:20 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "ast_struct.h"
# include "env_struct.h"
# include "signals.h"
# include "expand.h"
# include "error_code.h"
# include <sys/wait.h>
# include <fcntl.h>
# include "../../lib/libft/header/libft.h"

int		execute_ast(t_node *ast_node, t_shell *shell);

/*execute command*/
int		execute_command(t_node *cmd, t_shell *shell);
int		handle_parent_process(pid_t pid, t_shell *shell);
void	execute_child_process(t_node *cmd, t_shell *shell);
char	*find_cmd_path(char *cmd, t_shell *shell);
char	*check_all_paths(char **paths, char *cmd);

/*execute builtin*/
int		execute_builtin(char **args, t_shell *shell);
bool	is_builtin(char *cmd);

/*execute pipes*/
int		execute_pipe(t_node *pide, t_shell *shell);
int		create_pipe(int pipe_fd[2], t_shell *shell);
void	redirect_output_to_pipe(int pipe_fd[2]);
void	redirect_input_from_pipe(int pipe_fd[2]);
int		execute_pipe_brother(int pipe_fd[2], t_node *pipe, t_shell *shell);

/*execute logical*/
int		execute_logical(t_node *logic, t_shell *shell);

/*execute subshell*/
int		execute_subshell(t_node *subshell, t_shell *shell);

/*handle redirection in execution*/
bool	apply_redirections(t_redirection *redir, t_shell *shell);
bool	single_redirection(t_redirection *redir, t_shell *shell);
int		open_redirection_file(t_redirection *redir, t_shell *shell);
int		handle_heredoc(t_redirection *redir, t_shell *shell);
bool	write_heredoc_lines(int fd, t_redirection *redir, t_shell *shell);

/*free exec*/
void	free_array(char **array);

#endif