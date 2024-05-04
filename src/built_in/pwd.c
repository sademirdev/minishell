#include "built_in.h"

static void	handle_pwd()
{
	char cwd[1024];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
		return;
}