#include "../../inc/built_in.h"
#include <unistd.h>
#include <stdio.h>

int64_t	handle_pwd(void)
{
	char	cwd[1024];

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
