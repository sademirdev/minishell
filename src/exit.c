#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static bool	ft_is_digit(char *c);
static void	ft_putstr_fd(char *str, int fd);

int64_t	handle_exit(t_token *token)
{
	int64_t		exit_code;

	exit_code = 1;
	if (!token)
	{
		ft_putstr_fd("exit\n", 1);
		exit (1);
	}
	ft_putstr_fd("exit\n", 1);
	if (!ft_is_digit(token->next->data))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(token->next->data, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 255;
		exit (exit_code);
	}
	exit_code = atoi(token->next->data); // ft_atoi yaz
	if (token->next->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_code = 1;
		exit (exit_code);
	}
	// free all the malloced memory
	exit (exit_code);
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
