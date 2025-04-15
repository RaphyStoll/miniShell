#include "env_struct.h"
#include "utils.h"
#include "builtin.h"

bool is_valid_identifier(const char *str)
{
	int i;

	i = 0;
	if (!str || str[0] == '\0')
		return (false);
	if(!((str[0] >= 'a' && str[0] <= 'z')
		|| (str[0] >= 'A' && str[0] <= 'Z')
		|| str[0] == '_'))
		return (false);
	while (str[i++])
	{
		if (!((str[i] >= 'a' && str[i] <= 'z')
			|| (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9')
			|| str[i] == '_'))
			return (false);
	}
	return (true);
}

t_env	*add_env_node2(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (*env_list);
}