#include "bultin.h"
#include "error_code.h"

int builtin_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd");
		return (GENERIC_ERROR);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}

/*
int main ()
{
	if (!builtin_pwd())
		return 1;
	return 0;
}
*/