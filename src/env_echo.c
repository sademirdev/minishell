#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	handle_env(t_token *token, t_state *state)
{
	int		i;

	if (!token || !state)
	{
		state->err = 1;
		return (state->err);
	}
	if (token->next && token->next->type == CMD)
	{
		state->err = 1;
		return (state->err);
	}
	i = 0;
	while (state->env[i])
		printf("%s\n", state->env[i++]);
	state->err = 0;
	return (state->err);
}

static char	*get_buffer(t_token *temp, t_state *state)
{
	char	*buffer;

	buffer = ft_strdup("");
	if (!buffer)
	{
		state->err = 1;
		return (free(buffer), NULL);
	}
	while (temp)
	{
		if (temp->type == ARG)
		{
			buffer = ft_strjoin(buffer, temp->data, 1);
			if (!buffer)
			{
				state->err = 1;
				return (free(buffer), NULL);
			}
			if (temp->next)
			{
				buffer = ft_strjoin(buffer, " ", NULL);
				if (!buffer)
				{
					state->err = 1;
					return (free(buffer), NULL);
				}
			}
		}
		temp = temp->next;
	}
	return (buffer);
}

int	handle_echo(t_token *token, t_state *state)
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
		state->err = 1;
		return (state->err);
	}
	printf("%s", buffer);
	if (token->next && ft_strncmp(token->next->data, "-n", 2) != 0)
		printf("\n");
	return (0);
}
