#include "../../inc/built_in.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int64_t	handle_echo(t_built_in *built)
{
	t_built_in	*temp;
	char		*buffer;
	bool		new_line;

	buffer = ft_strdup("");
	if (!built || !buffer)
		return (free(buffer), 1);
	temp = built->next;
	new_line = ft_strcmp(temp->data, "-n") == 0;
	if (new_line)
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
	if (!new_line)
		printf("\n");
	return (0);
}
