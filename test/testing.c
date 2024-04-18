#include "testing.h"
#include <sys/wait.h>
#include <unistd.h>

int		err = 0;
int		err_in = 0;

void	run_token_test(void);
void	run_separator_test(void);
void	run_dollar_test(t_state *state);

int	main(int argc, char **argv)
{
	extern char **environ;
	char **env;
	int i;

	i = 0;
	while (environ[i])
		i++;
	env = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (1);
	i = 0;
	while (environ[i])
	{
		env[i] = ft_strdup(environ[i]);
		if (!env[i])
			return (1);
		i++;
	}
	env[i] = NULL;

	(void)argc;
	(void)argv;
	t_state s = {
		172,
		argv,
		env,
	};

	// int pid = fork();
	run_dollar_test(&s);
	// if (pid == 0)
	// {
	// }
	// else
	// {
	// 	waitpid(pid, NULL, 0);
	// 	// run_separator_test();
	// }
}