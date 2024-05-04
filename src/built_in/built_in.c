#include "built_in.h"

void	handle_built_in(t_built_in *built)
{
	if (!built)
		return ; // todo(apancar): handle error
	if ((ft_strncmp(built->data, "echo", 4) == 0) && ft_strlen(built->data) == 4)
		handle_echo(built);
	else if ((ft_strncmp(built->data, "cd", 2) == 0) && ft_strlen(built->data) == 2)
		handle_cd(built);
	else if ((ft_strncmp(built->data, "pwd", 3) == 0) && ft_strlen(built->data) == 3)
		handle_pwd(built);
	else if ((ft_strncmp(built->data, "export ", 7) == 0) && ft_strlen(built->data) == 7)
		handle_export(built);
	else if ((ft_strncmp(built->data, "unset", 5) == 0) && ft_strlen(built->data) == 5)
		handle_unset(built);
	else if ((ft_strncmp(built->data, "env", 3) == 0) && ft_strlen(built->data) == 3)
		handle_env(built);
	else if ((ft_strncmp(built->data, "exit", 4) == 0) && ft_strlen(built->data) == 4)
		handle_exit(built);
}