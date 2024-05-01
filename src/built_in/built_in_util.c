#include "built_in.h"

bool is_built_in(t_built_in *built)
{
	if (!built)
		return (false);
	if (built->type != CMD)
		return (false);
	if ((ft_strncmp(built->data, "echo", 4) == 0) && ft_strlen(built->data) == 4)
		return (true);
	else if ((ft_strncmp(built->data, "cd", 2) == 0) && ft_strlen(built->data) == 2)
		return (true);
	else if ((ft_strncmp(built->data, "pwd", 3) == 0) && ft_strlen(built->data) == 3)
		return (true);
	else if ((ft_strncmp(built->data, "export", 6) == 0) && ft_strlen(built->data) == 6)
		return (true);
	else if ((ft_strncmp(built->data, "unset", 5) == 0) && ft_strlen(built->data) == 5)
		return (true);
	else if ((ft_strncmp(built->data, "env", 3) == 0) && ft_strlen(built->data) == 3)
		return (true);
	else if ((ft_strncmp(built->data, "exit", 4) == 0) && ft_strlen(built->data) == 4)
		return (true);
    return (false);
}
