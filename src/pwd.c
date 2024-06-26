#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	handle_pwd(void)
{
	char	cwd[1024];

	if ((getcwd(cwd, sizeof(cwd)) == 0) || ft_strlen(cwd) == 0)
		return (FAILURE);
	printf("%s\n", cwd);
	return (SUCCESS);
}
