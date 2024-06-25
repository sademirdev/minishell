#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int	handle_env(t_token *token, t_state *state, t_cmd *cmd)
{
	int		i;

	if (!token || !state)
	{
		state->status = 1;
		return (1);
	}
	if (token->next && token->next->type == CMD)
	{
		state->status = 1;
		return (print_err("##handle_env.if##", 1), 1);
	}
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
	state->status = 0;
	return (1);
}



static char	*get_buffer(t_token *temp)
{
	char	*buffer;

	buffer = ft_strdup("");
	if (!buffer)
		return (NULL);
	while (temp)
	{
		if (temp->type == ARG)
		{
			buffer = ft_strjoin(buffer, temp->data, 1);
			if (!buffer)
				return (NULL);
			if (temp->next)
			{
				buffer = ft_strjoin(buffer, " ", NULL);
				if (!buffer)
					return (NULL);
			}
		}
		temp = temp->next;
	}
	return (buffer);
}

int	handle_echo(t_token *token, t_state *state, t_cmd *cmd)
{
	t_token	*temp;
	char		*buffer;

	temp = NULL;
	buffer = NULL;
	if (!token->next)
		return (SUCCESS);
	temp = token->next;
	if (temp)
		if (ft_strncmp(temp->data, "-n", 2) == 0)
			temp = temp->next;
	buffer = get_buffer(temp);
	if (!buffer)
		return (FAILURE);
	if (token->next && ft_strncmp(token->next->data, "-n", 2) != 0)
		buffer = ft_strjoin(buffer, "\n", 0);
	if (temp && temp->next && (temp->next->type == RED_R || temp->next->type == RED_RR ||
			temp->next->type == PIPE))
		write(cmd->out, buffer, ft_strlen(buffer));
	else
		write(STDOUT_FILENO, buffer, ft_strlen(buffer));
	return (free(buffer), SUCCESS);
}
