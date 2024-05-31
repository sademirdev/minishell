#include "minishell.h"
#include <stdlib.h>

int	handle_unset(t_token *token)
{
	extern char	**environ;
	int		i;
	t_token	*temp;

	temp = token->next;
	while (temp)
	{
		i = -1;
		while (environ[++i])
		{
			if (ft_strncmp(environ[i], temp->data, ft_strlen(temp->data)) == 0)
			{
				while (environ[i + 1])
				{
					environ[i] = environ[i + 1];
					i++;
				}
				environ[i] = NULL;
				break ;
			}
		}
		temp = temp->next;
	}
	return (0);
}
