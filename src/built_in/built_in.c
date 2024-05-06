#include "../inc/built_in.h"

int64_t	handle_built_in(t_built_in *built)
{
	int64_t		result;

	result = 0;
	if (!built)
		result = 1 ;
	if ((ft_strncmp(built->data, "echo", 4) == 0) && ft_strlen(built->data) == 4)
		result = handle_echo(built);
	else if ((ft_strncmp(built->data, "cd", 2) == 0) && ft_strlen(built->data) == 2)
		result = handle_cd(built);
	else if ((ft_strncmp(built->data, "pwd", 3) == 0) && ft_strlen(built->data) == 3)
		result = handle_pwd(built);
	else if ((ft_strncmp(built->data, "export ", 7) == 0) && ft_strlen(built->data) == 7)
		result = handle_export(built);
	else if ((ft_strncmp(built->data, "unset", 5) == 0) && ft_strlen(built->data) == 5)
		result = handle_unset(built);
	else if ((ft_strncmp(built->data, "env", 3) == 0) && ft_strlen(built->data) == 3)
		result = handle_env(built);
	else if ((ft_strncmp(built->data, "exit", 4) == 0) && ft_strlen(built->data) == 4)
		result = handle_exit(built);
	return (result);
}