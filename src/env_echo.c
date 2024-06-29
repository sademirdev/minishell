#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	handle_env(t_token *token, t_state *state, t_cmd *cmd)
{
	int		i;

	if (!token || !state)
		return (FAILURE);
	if (token->next && token->next->type == CMD)
		return (FAILURE);
	i = 0;
	while (state->env[i])
	{
		if (state->env[i] && token && token->next && (token->next->type == RED_R || token->next->type == RED_RR ||
				token->next->type == PIPE))
		{
			write(cmd->out, state->env[i], ft_strlen(state->env[i]));
			write(cmd->out, "\n", 1);
		}
		else
		{
			write(1, state->env[i], ft_strlen(state->env[i]));
			write(1, "\n", 1);
		}
		i++;
	}
	return (SUCCESS);
}

static int	get_buffer_len(t_token *arg, bool n)
{
	int	len;
	int	space;
	int	newline;

	len = 0;
	if (arg && arg->data)
		len = ft_strlen(arg->data);
	newline = 0;
	if (n)
		newline = 1;
	space = -1;
	while (arg)
	{
		len += ft_strlen(arg->data);
		if (arg->next)
			space++;
		arg = arg->next;
	}
	return (len + space + newline + 1);
}

static char	*merge_args(t_token *arg, bool n)
{
	char		*buffer;
	int			i;
	int			j;

	buffer = (char *) malloc(sizeof(char) * get_buffer_len(arg, n));
	if (!buffer)
		return (NULL);
	j = 0;
	while (arg)
	{
		i = 0;
		while (arg->data[i])
			buffer[j++] = arg->data[i++];
		if (arg->next)
			buffer[j++] = ' ';
		arg = arg->next;
	}
	if (!n)
		buffer[j++] = '\n';
	buffer[j] = '\0';
	return (buffer);
}

static void dprint(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}

static bool	is_echo_n_flag(const char *flag)
{
	int	i;

	if (!(flag[0] == '-' && flag[1] == 'n'))
		return (false);
	i = 2;
	while (flag[i])
	{
		if (flag[i] != 'n')
			return (false);
		i++;
	}
	return (true);
}

int	handle_echo(t_token *token, t_state *state, t_cmd *cmd)
{
	char *buffer;
	bool	n;

	if (!token || !state || !cmd)
		return (FAILURE);
	if (!token->next)
		return (dprint(STDOUT_FILENO, "\n"), SUCCESS);
	token = token->next;
	n = is_echo_n_flag(token->data);
	if (n)
		token = token->next;
	while (token && is_echo_n_flag(token->data))
		token = token->next;
	buffer = merge_args(token, n);
	if (!buffer)
		return (FAILURE);
	dprint(STDOUT_FILENO, buffer);
	return (SUCCESS);
}
