#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"

void	ft_exit_error(t_token *token, char *message, t_error error_code)
{
	free_all(token);
	nbr_error(error_code, message);

	exit(error_code);
}