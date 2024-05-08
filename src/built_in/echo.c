#include "../../inc/built_in.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int64_t	handle_echo(t_built_in *built)
{
	t_built_in	*temp;
	char		*buffer;

	buffer = ft_strdup("");
	if (!buffer)
		return (free(buffer), 1);
	temp = built->next;
	if (ft_strcmp(temp->data, "-n") == 0)
		temp = temp->next;
	while (temp && temp->type == ARG)
	{
		buffer = ft_strjoin(buffer, temp->data);
		if (!buffer)
			return (free(buffer), 1);
		if (temp->next && temp->next->type == ARG)
		{
			buffer = ft_strjoin(buffer, " ");
			if (!buffer)
				return (free(buffer), 1);
		}
		temp = temp->next;
	}
	printf("%s", buffer);
	if (built->next && ft_strcmp(built->next->data, "-n") == 0)
		printf("\n");
	return (0);
}
