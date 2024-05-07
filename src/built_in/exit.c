#include "built_in.h"

static bool	ft_is_digit(char *c)
{
	int	i;

	i = 0;
	if (c[i] == '-' || c[i] == '+')
		i++;
	while (c[i])
	{
		if (!ft_isdigit(c[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_putstr_fd(char *str, int fd)
{
	if (str)
		write(fd, str, ft_strlen(str));
	else
		return ;
}

int64_t	handle_exit(t_built_in *built)
{
	t_built_in	*temp;
	int64_t		exit_code;

	exit_code = 0;
	if (!built)
		exit (0);
	temp = built;
	ft_putstr_fd("exit\n", 1);
	if (!ft_is_digit(temp->next))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(temp->next, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit_code = 255;
	}
	else
		exit_code = ft_atoi(temp->next);
	if (temp->next->next)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_code = 1;
	}
	// free all the malloced memory
	exit (exit_code);
	return (1);
}
