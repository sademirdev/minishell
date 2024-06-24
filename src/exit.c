#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static bool	ft_is_digit(char *c);

// static int print_err_with_status(const int err, t_state *state, int status)
// {
// 		print_err("exit", err);
// 		state->status = status;
// 		return (status);
// }

int	handle_exit(t_token *token, t_state *state)
{
	long	exit_code; // todo(sademir): is it ok

	if (!token)
	{
		print_err("exit", EINVAL);
		state->status = 1;
		return (1);
	}
	if (token && token->next && token->next->next)
	{
		print_err("exit", EINVAL);
		state->status = 1;
		return (1);
	}
	write (2, "exit\n", 5);
 	if (token->next && !ft_is_digit(token->next->data))
	{
		print_err("exit", ENOENT);
		state->status = ENOENT;
		return (1);
	}
	if (token->next)
	{
		exit_code = ft_atoi(token->next->data);
		if (exit_code < 0)
		{
			return (state->status = (int)(256 + (exit_code % 256)), 1);
		}
		state->status = (int)(exit_code % 256);
		return (1);
	}
	else
		state->status = 0;
	// free all the malloced memory
	return (0);
}

static bool	ft_is_digit(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '-' || c[i] == '+')
		i++;
	while (c[i])
	{
		if (!(c[i] >= '0' && c[i] <= '9'))
			return (false);
		i++;
	}
	return (true);
}
