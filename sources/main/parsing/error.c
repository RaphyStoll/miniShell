#include "../../../includes/main/lexing.h"
#include "../../../includes/main/parsing.h"

void	ft_exit_error(t_token *token, char *message, t_error error_code)
{
	free_all(token);
	nbr_error(error_code, message);
	exit(error_code);
}

void nbr_error(t_error error_code, char *message) {
	if (error_code == GENERIC_ERROR)
		printf(RED BOLD"Error : General\n"NC);
	else if (error_code == USAGE_ERROR)
		printf(RED BOLD"Error : Usage\n"NC);
	else if (error_code == MATH_ERROR)
		printf(RED BOLD"Error : Math\n"NC);
	else if (error_code == SPECIFIC_ERROR_42)
		printf(RED BOLD"Error : 42 is 42\n"NC);
	else if (error_code == PERMISSION_ERROR)
		printf(RED BOLD"Error : No permission\n"NC);
	else if (error_code == SYNTAX_ERROR)
		printf(RED BOLD"Error : Syntax\n"NC);
	else if (error_code == COMMAND_NOT_FOUND)
		printf(RED BOLD"Error : Command not found\n"NC);
	else if (error_code == WRAPPER_ERROR)
		printf(RED BOLD"Error : Wrapper\n"NC);
	else
		perror(RED BOLD"Error"NC);
	printf(YELLOW"%s\n"NC, message);
	return ;
}

