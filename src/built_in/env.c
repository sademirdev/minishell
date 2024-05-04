#include "built_in.h"

void	handle_env(t_built_in *built)
{
	extern char	**environ;
	char		**env;
	char		*env_var;
	char		*value;

	if (built->next->data != CMD)
	{
		// todo(apancar): handle error
		return ;
	}
	// todo(apancar): what we do if built->next->data == CMD
	env = environ;
	while (*env != NULL)
	{
		env_var = *env;
		value = getenv(env_var);
		if (value)
			printf("%s=%s\n", env_var, value);
		else
			printf("%s=(null)\n", env_var);
		env++;
	}
}
