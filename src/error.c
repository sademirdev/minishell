#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void	err_at(const char *cmd)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, " \n", 2);
}

// void	print_fatal()
// {

// }

void	print_err(const char *msg, t_state *state, const int status)
{
	if (state)
		state->status = status;
	err_at(msg);
}
