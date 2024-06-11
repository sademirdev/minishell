#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int	handle_env(t_token *token, t_state *state)
{
	int		i;

	if (!token || !state)
		return (1);
	if (token->next && token->next->type == CMD)
		return (1);
	i = 0;
	while (state->env[i])
		printf("%s\n", state->env[i++]);
	return (0);
}

static char	*get_buffer(t_token *temp)
{
	char	*buffer;

	buffer = ft_strdup("");
	while (temp && temp->type == ARG)
	{
		buffer = ft_strjoin(buffer, temp->data, 1);
		if (!buffer)
			return (free(buffer), NULL);
		if (temp->next && temp->next->type == ARG)
		{
			buffer = ft_strjoin(buffer, " ", NULL);
			if (!buffer)
				return (free(buffer), NULL);
		}
		temp = temp->next;
	}
	return (buffer);
}

int	handle_echo(t_token *token)
{
	t_token	*temp;
	char	*buffer;

	temp = NULL;
	buffer = NULL;
	if (token->next)
		temp = token->next;
	else
		return (printf("\n"), 0);
	if (temp)
		if (ft_strncmp(temp->data, "-n", 2) == 0)
			temp = temp->next;
	buffer = get_buffer(temp);
	if (!buffer)
		return (1);
	printf("%s", buffer);
	if (token->next && ft_strncmp(token->next->data, "-n", 2) != 0)
		printf("\n");
	return (0);
}
