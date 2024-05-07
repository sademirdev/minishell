#include "../../inc/built_in.h"
#include <stdlib.h>

int64_t	handle_unset(t_built_in *built)
{
	extern char	**environ;
	int64_t		i;
	t_built_in	*temp;

	temp = built->next;
	while (temp)
	{
		i = 0;
		while (environ[i])
		{
			if (ft_strncmp(environ[i], temp->data, ft_strlen(temp->data)) == 0)
			{
				free(environ[i]);
				while (environ[i])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				break ;
			}
			i++;
		}
		temp = temp->next;
	}
	return (0);
}
