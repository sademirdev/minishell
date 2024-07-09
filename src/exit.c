#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static bool	ft_is_digit(char *c);

int	exec_exit(t_state *state, t_token *token)
{
	int	exit_code;

	exit_code = 0;
	if (!token)
		print_fatal_err("invalid argument\n", 2);
	if (token && token->next && token->next->next)
		return (print_exec_err(state, token, 1, ERR_TOO_MANY_ARG));
	if (token->next && !ft_is_digit(token->next->data))
		return (print_exec_err(state, token, 255, ERR_NUMERIC_ARG_REQUIRED),
			exit(255), FAILURE);
	if (token->next)
	{
		exit_code = ft_atoi(token->next->data);
		if (exit_code < 0)
			return (print_exec_err(state, token, \
				(int)(256 + (exit_code % 256)), ENO_OTHER), exit(exit_code),
					FAILURE);
		return (print_exec_err(state, token, \
			(int)(exit_code % 256), ENO_OTHER), exit(exit_code), FAILURE);
		dprintf(2, "[DEBUG]: at\n");
	}
	return (exit(exit_code), SUCCESS);
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
