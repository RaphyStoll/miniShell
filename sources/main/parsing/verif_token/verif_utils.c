#include "lexing_struct.h"
#include <stdlib.h>

bool	is_simple_redirection(t_token *token)
{
	// Must be at start of command
	if (token->prev != NULL)
		return false;

	if (token->type != REDIRECT_IN
		&& token->type != REDIRECT_OUT
		&& token->type != APPEND
		&& token->type != HEREDOC)
		return false;
	if (!token->next || token->next->type != WORD)
		return false;
	// That WORD must be the last token
	if (token->next->next != NULL)
		return false;
	return true;
}
