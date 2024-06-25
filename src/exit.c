#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static bool	ft_is_digit(char *c);

int	handle_exit(t_token *token, t_state *state)
{
	long	exit_code; // todo(sademir): is it ok

	if (!token)
	{
		print_err("invalid argument", state, 1);
		exit(2); // dispose minishell before exit
	}
	if (token && token->next && token->next->next)
	{
		print_err("##handle_exit.if2##", EINVAL);
		state->status = 1;
		return (FAILURE);
	}
	write (2, "exit\n", 5);
 	if (token->next && !ft_is_digit(token->next->data))
	{
		print_err("##handle_exit.if3##", ENOENT);
		state->status = ENOENT;
		return (FAILURE);
	}
	if (token->next)
	{
		exit_code = ft_atoi(token->next->data);
		if (exit_code < 0)
		{
			return (state->status = (int)(256 + (exit_code % 256)), 1);
		}
		state->status = (int)(exit_code % 256);
		return (FAILURE);
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
