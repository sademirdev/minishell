#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

static bool	ft_is_digit(char *c);
// static int	ft_atoi(const char *str);

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
		print_err("exit", errno);
		state->status = 255;
		return (1);
	}
	if (token->next)
	{
		exit_code = atoi(token->next->data); // write ft_atoi
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

// static int	ft_atoi(const char *str)
// {
// 	int		i;
// 	int		sign;
// 	int		result;

// 	i = 0;
// 	sign = 1;
// 	result = 0;
// 	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
// 		i++;
// 	if (str[i] == '-' || str[i] == '+')
// 	{
// 		if (str[i] == '-')
// 			sign = -1;
// 		i++;
// 	}
// 	while (str[i] >= '0' && str[i] <= '9')
// 	{
// 		result = result * 10 + str[i] - '0';
// 		i++;
// 	}
// 	return (result * sign);
// }
