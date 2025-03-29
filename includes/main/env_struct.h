/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Charlye <Charlye@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 08:45:28 by Charlye           #+#    #+#             */
/*   Updated: 2025/03/29 09:25:59 by Charlye          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "../../lib/libft/header/libft.h"

typedef struct s_env
{
	char			*type;
	char			*value;
	struct s_env	*next;
}	t_env;

#endif