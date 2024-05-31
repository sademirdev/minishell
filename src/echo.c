#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int	handle_echo(t_token *token)
{
	t_token	*temp;
	char		*buffer;

	temp = NULL;
	buffer = ft_strdup("");
	if (!buffer)
		return (free(buffer), 1);
	if (token->next)
		temp = token->next;
	else
	{
		printf("\n");
		return (0);
	}
	if (temp)
		if (ft_strncmp(temp->data, "-n", 2) == 0)
			temp = temp->next;
	while (temp && temp->type == ARG)
	{
		buffer = ft_strjoin(buffer, temp->data, 1);
		if (!buffer)
			return (free(buffer), 1);
		if (temp->next && temp->next->type == ARG)
		{
			buffer = ft_strjoin(buffer, " ", 1);
			if (!buffer)
				return (free(buffer), 1);
		}
		temp = temp->next;
	}
	printf("%s", buffer);
	if (token->next && ft_strncmp(token->next->data, "-n", 2) != 0)
		printf("\n");
	return (0);
}
