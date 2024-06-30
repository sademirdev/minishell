#include "minishell.h"
#include <unistd.h>

int	exec_pwd(t_cmd *cmd)
{
	char	cwd[PATH_MAX];

	if ((getcwd(cwd, sizeof(cwd)) == 0) || ft_strlen(cwd) == 0)
		return (FAILURE);
	dprintln(cmd->out, cwd);
	return (SUCCESS);
}
