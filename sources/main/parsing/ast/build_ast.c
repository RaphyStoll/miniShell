#include "../../../../includes/main/ast.h"
#include "../../../../includes/main/lexing.h"

t_node	*build_ast(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	return (parse_logical(&tokens));
}