#include "../../inc/built_in.h"
#include <stdlib.h>
#include <stdio.h>

int64_t	handle_env()
{
	extern char	**environ;
	char		**env;
	char		*value;

	// if (built->next->type != CMD)
	// {
	// 	// todo(apancar): handle error
	// 	return (1);
	// }
	// todo(apancar): what we do if built->next->data == CMDenv
	env = environ;
	while (*env != NULL)
	{
		value = getenv(*env);
		if (value)
			printf("%s=%s\n", *env, value);
		else
			printf("%s=(null)\n", *env);
		env++;
	}
	return (0);
}

int	main()
{
	// t_built_in	*temp;

	// temp = (t_built_in *)malloc(sizeof(t_built_in));
	// temp->data = "env";
	// temp->type = CMD;
	handle_env();
	return (0);
}