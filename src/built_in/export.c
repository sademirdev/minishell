#include "../../inc/built_in.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

static void	export_var(void)
{
	extern char	**environ;
	char		**env;
	char		*value;

	env = environ;
	while (*env != NULL)
	{
		value = getenv(*env);
		if (!value)
			printf("%s=(null)\n", *env);
		else
			printf("declare -x=%s\n", value);
		env++;
	}
}

static int64_t	env_add(char *var, char *temp)
{
	extern char	**environ;
	char		**env;
	char		*new_var;
	int64_t		i;

	i = 0;
	new_var = ft_strdup("");
	if (!new_var)
		return (1);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], var, ft_strlen(var)) == 0)
		{
			new_var = ft_strjoin(new_var, temp);
			if (!new_var)
				return (free (new_var), 1);
			free(environ[i]);
			environ[i] = new_var;
			return (0);
		}
		i++;
	}
	new_var = ft_strjoin(new_var, temp);
	if (!new_var)
		return (1);
	env = (char **)malloc(sizeof(char *) * (i + 2));
	if (!env)
		return (1);
	i = 0;
	while (environ[i] != NULL)
	{
		env[i] = environ[i];
		i++;
	}
	env[i] = new_var;
	env[i + 1] = NULL;
	environ = env;
	// return (environ)???
	return (0);
}

int64_t	handle_export(t_built_in *built)
{
	int64_t		i;
	char		**var;
	t_built_in	*temp;

	if (!built)
		return (1);
	if (built->next == NULL)
	{
		export_var();
		return (0);
	}
	var = NULL;
	temp = built->next;
	var = ft_split(temp->data, '=');
	if (!var)
		return (1);
	i = 0;
	if (env_add(var[0], temp->data) == 1)
	{
		while (var[i] != NULL)
			free(var[i++]);
		free(var);
		return (1);
	}
	return (0);
}
