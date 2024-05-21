#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

int64_t	handle_env(t_token *token)
{
	extern char	**environ;
	char		**env;
	char		*value;

	if (!token)
		return (1);
	if (token->next && token->next->type == CMD)
		return (1);
	env = environ;
	if (!env || !*env)
	{
		printf("env: environ is empty\n");
		return (1);
	}
	while (*env != NULL)
	{
		value = getenv(*env);
		if (value == NULL)
			printf("%s=(null)\n", *env);
		else
			printf("%s=%s\n", *env, value);
		env++;
	}
	return (0);
}
