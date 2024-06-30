#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int	exec_cd(t_state *state, t_token *token)
{
	const char	*home;

	if (!token)
		return (FAILURE);
	if (!token->next)
	{
		home = env_get_value(state, "HOME");
		if (!home)
			return (print_exec_err(state, token, 1, ERR_HOME_NOT_SET));
		if (chdir(home) == -1)
			return (print_exec_err(state, token, 114, ERR_CANT_CHANGE_DIR));
		if (env_set_pwd(state) != SUCCESS)
			return (FAILURE);
		return (SUCCESS);
	}
	if (chdir(token->next->data) == -1)
		return (print_exec_err(state, token, 120, ERR_CANT_CHANGE_DIR));
	if (env_set_pwd(state) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
