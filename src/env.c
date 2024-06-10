#include "minishell.h"
#include <stdlib.h>
#include <stdio.h>

// int	handle_env(t_token *token)
// {
// 	extern char	**environ;
// 	char		**env;
// 	char		*value;

// 	if (!token)
// 		return (1);
// 	if (token->next && token->next->type == CMD)
// 		return (1);
// 	env = environ;
// 	if (!env || !*env)
// 	{
// 		printf("env: environ is empty\n");
// 		return (1);
// 	}
// 	while (*env != NULL)
// 	{
// 		value = getenv(*env);
// 		if (value == NULL)
// 			printf("%s=(null)\n", *env);
// 		else
// 			printf("%s\n", *env);
// 		env++;
// 	}
// 	return (0);
// }


int	handle_env(t_token *token, t_state *state)
{
	char	*value;
	int		i;

	if (!token || !state)
		return (1);
	if (token->next && token->next->type == CMD)
		return (1);
	i = 0;
	printf("state->env:%p\n", state->env);
	while (state->env[i])
	{
		value = getenv(state->env[i]);
		if (!value)
			printf("%s=(null)\n", state->env[i]);
		else
			printf("%s\n", state->env[i]);
		i++;
	}
	return (0);
}
