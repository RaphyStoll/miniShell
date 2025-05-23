/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chpasqui <chpasqui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 14:45:06 by Charlye           #+#    #+#             */
/*   Updated: 2025/05/01 12:12:46 by chpasqui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "minishell.h"
#include "../../../lib/libft/header/libft.h"

/**
 * @brief Expands the special variable `$?`.
 *
 * Appends the last command's exit status as a string to the result.
 *
 * @param result Pointer to the result string to update.
 * @return 1 on success, 0 on failure.
 */
bool	handle_exit_status(char **result, t_shell *shell)
{
	char	*value;
	char	*tmp;

	value = ft_itoa(shell->last_exit_status);
	if (!value)
		return (false);
	tmp = *result;
	*result = ft_strjoin(*result, value);
	free(tmp);
	free(value);
	if (!*result)
		return (false);
	return (true);
}

/**
 * @brief Handles expansion of a variable starting at current index.
 *
 * Extracts the variable name, retrieves its value from the environment,
 * and appends the result to the output string.
 *
 * @param result Pointer to the result string to update.
 * @param arg Input argument string.
 * @param i Pointer to the current index in the argument string.
 * @param env Environment variable list
 * @return 1 on success, 0 on failure.
 */
bool	handle_variable(char **result, char *arg, int *i, t_shell *shell)
{
	char	*type;
	char	*value;
	char	*tmp;
	int		start;

	start = *i;
	if (arg[*i] == '\0' || arg[*i] == ' ')
		return (handle_regular_char(result, '$'));
	while (arg[*i] && (ft_isalnum(arg[*i]) || arg[*i] == '_'))
		(*i)++;
	type = ft_strndup(&arg[start], *i - start);
	if (!type)
		return (false);
	value = get_env_value(shell, type);
	tmp = *result;
	if (value)
		*result = ft_strjoin(*result, value);
	else
		*result = ft_strjoin(*result, "");
	free(tmp);
	free(type);
	if (!*result)
		return (false);
	return (true);
}

/**
 * @brief Appends a single regular character to the result string.
 *
 * Handles characters that are not part of a variable expansion.
 *
 * @param result Pointer to the result string to update.
 * @param c Character to append.
 * @return 1 on success, 0 on failure.
 */
bool	handle_regular_char(char **result, char c)
{
	char	*tmp;
	char	*one_char;

	one_char = ft_strndup(&c, 1);
	if (!one_char)
		return (false);
	tmp = *result;
	*result = ft_strjoin(*result, one_char);
	free(tmp);
	free(one_char);
	if (!*result)
		return (false);
	return (true);
}
