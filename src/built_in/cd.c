#include "../../inc/built_in.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static bool	is_relative_path(const char *path)
{
	if (!path)
		return (false);
	if ((path[0] == '.' && path[1] == '/') || path[0] != '/')
		return (true);
	return (false);
}

static bool	is_absolute_path(const char *path)
{
	if (!path)
		return (false);
	if (path[0] == '/')
		return (true);
	return (false);
}

static int64_t	handle_relative_path(t_built_in *built)
{
	char		*temp_path;
	char		cwd[PATH_MAX];
	size_t		len;

	len = 0;
	if (!getcwd(cwd, PATH_MAX))
		return (1);
	if (chdir(cwd) == -1)
		return (1);
	len = ft_strlen(cwd) + ft_strlen(built->next->data) + 1;
	if (len > PATH_MAX)
		return (1);
	temp_path = malloc(sizeof(char) * (len + 1));
	if (!temp_path)
		return (1);
	ft_strlcpy(temp_path, cwd, ft_strlen(cwd) + 1);
	temp_path[ft_strlen(cwd)] = '/';
	ft_strlcpy(temp_path + ft_strlen(cwd) + 1, built->next->data, len);
	temp_path[len] = '\0';
	if (chdir(temp_path) == -1)
	{
		printf("cd: %s: No such file or directory\n", built->next->data);
		return (free(temp_path), 1);
	}
	return (free(temp_path), 0);
}

static int64_t	handle_absolute_path(t_built_in *built)
{
	char		cwd[PATH_MAX];

	if (chdir(built->next->data) == -1)
	{
		printf("cd: %s: No such file or directory\n", built->next->data);
		return (1);
	}
	return (0);
}

int64_t	handle_cd(t_built_in *built)
{
	const char	*home_path;
	char		cwd[PATH_MAX];

	if (!built)
		return (1);
	home_path = getenv("HOME");
	if (!home_path)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (!built->next)
	{
		if (chdir(home_path) == -1)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		return (0);
	}
	if (is_relative_path(built->next->data))
		return (handle_relative_path(built));
	else if (is_absolute_path(built->next->data))
		return (handle_absolute_path(built));
	return (1);
}
