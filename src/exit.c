#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static bool	ft_is_digit(char *c);
static void	ft_putstr_fd(char *str, int fd);

int	handle_exit(t_token *token, t_state *state)
{
	if (!token)
	{
		ft_putstr_fd("exit\n", 1);
		state->status = 1;
		return (1);
	}
	if (token && token->next && token->next->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		state->status = 1;
		return (1);
	}
	ft_putstr_fd("exit\n", 1);
 	if (token->next && !ft_is_digit(token->next->data))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(token->next->data, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		state->status = 255;
		return (1);
	}
	state->status = atoi(token->next->data); // ft_atoi yaz
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

static void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
}
