#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static bool	ft_is_digit(char *c);

int	handle_exit(t_token *token, t_state *state)
{
	int	exit_code;

	if (!token)
		fatal("invalid argument\n", 2);
	if (token && token->next && token->next->next)
		return (FAILURE);
	write(2, "exit\n", 5);
 	if (token->next && !ft_is_digit(token->next->data))
		return (FAILURE);
	if (token->next)
	{
		exit_code = ft_atoi(token->next->data);
		if (exit_code < 0)
			return (print_exec_err(state, token, (int)(256 + (exit_code % 256)), ERR_OTHER));
		return (print_exec_err(state, token, (int)(exit_code % 256), ERR_OTHER));
	}
	return (SUCCESS);
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
