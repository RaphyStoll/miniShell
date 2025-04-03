# include "../../../includes/main/env_struct.h"
//# include "error_code.h"
//# include "../../../lib/libft/header/libft.h"

void bultin_env(t_env *env)
{
	t_env *cur;
	cur = env;
	while(cur != NULL)
	{
		printf("%s=%s\n",cur->type, cur->value);
		cur = cur->next;
	}
	return ;
}




