#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

void	puterr(const char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

void	print_unknown_error(t_state *state)
{
	if (state->err == FAILURE)
	{
		state->status = 1;
		puterr("[print_unknown_error]: ");
		puterr("unknown error\n");
	}
}

int	print_exec_err(t_state *state, const t_token *token, int status, int err)
{
	state->err = HANDLED;
	state->status = status;
	if (err == ERR_OTHER)
		return (FAILURE);
	puterr(token->data);
	if (err == ENOENT)
		puterr(strerror(err));
	// todo(sademir): add other errors
	else if (err == ERR_NOT_A_VALID_IDENTIFIER)
		puterr(ERR_STR_NOT_A_VALID_IDENTIFIER);
	else
		puterr(ERR_STR_UNEXPECTED);
	return (FAILURE);
}

void	fatal(const char *msg, int err)
{
	puterr(msg);
	exit(err);
}

void	print_err(const char *msg, t_state *state, const int status)
{
	if (state)
		state->status = status;
	(void)msg;
}
