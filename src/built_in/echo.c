#include "../inc/built_in.h"

void	handle_echo(t_built_in *built)
{
	t_built_in	*temp;
	char		*buffer;

	buffer = ft_strdup("");
	if (!built)
		return ;
	temp = built;
	while (temp)
	{
		temp = temp->next;
		if (temp->type == ARG)
		{
			buffer = ft_strjoin(buffer, temp->data);
			if (!buffer)
			{
				free(buffer);
				return ;
			}
		}
		else if (is_meta(temp->type))
		{
			//redirect (buffer) to meta
		}
		else
		{
			printf("%s", buffer);
			free (buffer);
		}
	}
}

/*
echo "Hello, World!"
echo "Hello, World!" > file
echo "Hello, World!" >> file
echo "Hello, World!" | cat -e
echo Hello, World!
echo -n Hello, World!
echo | cat -e
echo > file
echo >> file
< file echo "Hello, World!"
< file echo "Hello, World!" > file
< file echo "Hello, World!" >> file
*/
