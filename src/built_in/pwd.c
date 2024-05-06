#include "built_in.h"

int64_t	handle_pwd()
{
	char cwd[1024];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		if (ft_strlen(cwd) == 0)
			return (1);
		printf("%s\n", cwd);
		return (0);
	}
	else
		return (1);
}