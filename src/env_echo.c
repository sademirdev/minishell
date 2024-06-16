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
		return (print_err(token->next->data, ERR_FILE_NOT_VALID), 1);
	}
	i = 0;
	while (state->env[i])
	{
		if (state->env[i] && token && token->next && (token->next->type == RED_R || token->next->type == RED_RR ||
				token->next->type == PIPE))
		{
			write (cmd->out, state->env[i], ft_strlen(state->env[i]));
			write (cmd->out, "\n", 1);
		}
		else
		{
			write (1, state->env[i], ft_strlen(state->env[i]));
			write (1, "\n", 1);
		}
		i++;
	}
	state->status = 0;
	return (1);
}



static char	*get_buffer(t_token *temp, t_state *state)
{
	char	*buffer;

	buffer = ft_strdup("");
	if (!buffer)
	{
		state->status = 1;
		return (free(buffer), NULL);
	}
	while (temp)
	{
		if (temp->type == ARG)
		{
			buffer = ft_strjoin(buffer, temp->data, 1);
			if (!buffer)
			{
				state->status = 1;
				return (free(buffer), NULL);
			}
			if (temp->next)
			{
				buffer = ft_strjoin(buffer, " ", NULL);
				if (!buffer)
				{
					state->status = 1;
					return (free(buffer), NULL);
				}
			}
		}
		temp = temp->next;
	}
	return (buffer);
}

int	handle_echo(t_token *token, t_state *state, t_cmd *cmd)
{
	t_token	*temp;
	char	*buffer;

	temp = NULL;
	buffer = NULL;
	if (token->next)
		temp = token->next;
	else
		return (free(buffer), 0);
	if (temp)
		if (ft_strncmp(temp->data, "-n", 2) == 0)
			temp = temp->next;
	buffer = get_buffer(temp, state);
	if (!buffer)
	{
		state->status = 1;
		return (state->status);
	}
	if (token->next && ft_strncmp(token->next->data, "-n", 2) != 0)
		buffer = ft_strjoin(buffer, "\n", 0);
	if (temp && temp->next && (temp->next->type == RED_R || temp->next->type == RED_RR ||
			temp->next->type == PIPE))
		write (cmd->out, buffer, ft_strlen(buffer));
	else
		write (1, buffer, ft_strlen(buffer));
	free(buffer);
	return (0);
}
