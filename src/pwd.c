#include "minishell.h"
#include <unistd.h>

int	exec_pwd(t_cmd *cmd, t_state *state)
{
	char	cwd[PATH_MAX];

	if ((getcwd(cwd, sizeof(cwd)) == 0) || ft_strlen(cwd) == 0)
		return (FAILURE);
	dprintln(cmd->bout, cwd);
	state->status = 0;
	return (SUCCESS);
}
