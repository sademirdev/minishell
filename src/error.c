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
		puterr("unknown error\n");
	}
}
int	print_exec_err(t_state *state, const t_token *token, int status, int err)
{
	state->err = HANDLED;
	state->status = status;
	if (err == ERR_OTHER)
		return (FAILURE);
	if (err < 30000)
	{
		puterr(token->data);
		puterr(": ");
	}
	if (err == ENOENT)
		puterr(strerror(err));
	if (err == ERR_CMD_NOT_FOUND)
		puterr(ERR_STR_CMD_NOT_FOUND);
	// todo(sademir): add other errors
	else if (err == ERR_NOT_A_VALID_IDENTIFIER)
		puterr(ERR_STR_NOT_A_VALID_IDENTIFIER);
	else if (err == ERR_NO_SUCH_FILE_OR_DIR)
		puterr(ERR_STR_NO_SUCH_FILE_OR_DIR);
	else if (err == ERR_NUMERIC_ARG_REQUIRED)
		puterr(ERR_STR_NUMERIC_ARG_REQUIRED);
	else if (err == ERR_TOO_MANY_ARG)
		puterr(ERR_STR_TOO_MANY_ARG);
	else if (err == ERR_PERMISSION_DENIED)
		puterr(ERR_STR_PERMISSION_DENIED);
	else if (err == ERR_PERMISSION_DENIED_BROKEN_PIPE)
		puterr(ERR_STR_PERMISSION_DENIED_BROKEN_PIPE);
	else if (err == ERR_IS_DIR)
		puterr(ERR_STR_IS_DIR);
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
