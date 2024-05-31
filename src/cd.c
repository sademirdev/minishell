#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static bool		is_relative_path(const char *path);
static bool		is_absolute_path(const char *path);
static int	handle_relative_path(t_token *token);
static int	handle_absolute_path(t_token *token);

int	handle_cd(t_token *token)
{
	const char	*home_path;

	if (!token)
		return (1);
	home_path = getenv("HOME");
	if (!home_path)
	{
		write(2, "cd: HOME not set\n", 17);
		return (1);
	}
	if (!token->next)
	{
		if (chdir(home_path) == -1)
		{
			write(2, "cd: HOME not set\n", 17);
			return (1);
		}
		return (1);
	}
	if (is_relative_path(token->next->data))
		return (handle_relative_path(token));
	else if (is_absolute_path(token->next->data))
		return (handle_absolute_path(token));
	return (0);
}

static bool	is_relative_path(const char *path)
{
	if (!path || *path == '\0')
		return (false);
	if (*path == '.' && (path[1] == '/' || \
			(path[1] == '.' && path[2] == '/' && path[2] != '\0')))
		return (true);
	if (path[0] != '/')
		return (true);
	return (false);
}

static bool	is_absolute_path(const char *path)
{
	if (!path)
		return (false);
	return (path[0] == '/');
}

static int	handle_relative_path(t_token *token)
{
	char		*temp_path;
	char		cwd[PATH_MAX];
	size_t		len;

	len = 0;
	if (!getcwd(cwd, PATH_MAX))
		return (1);
	if (chdir(cwd) == -1)
		return (1);
	len = ft_strlen(cwd) + ft_strlen(token->next->data) + 1;
	if (len > PATH_MAX)
		return (1);
	temp_path = malloc(sizeof(char) * (len + 1));
	if (!temp_path)
		return (free(temp_path), 1);
	ft_strlcpy(temp_path, cwd, ft_strlen(cwd) + 1);
	temp_path[ft_strlen(cwd)] = '/';
	ft_strlcpy(temp_path + ft_strlen(cwd) + 1, token->next->data, len);
	temp_path[len] = '\0';
	if (chdir(temp_path) == -1)
	{
		write (2,"No such file or directory\n", 27);
		free(temp_path);
		exit (1);
	}
	return (free(temp_path), 1);
}

static int	handle_absolute_path(t_token *token)
{
	if (chdir(token->next->data) == -1)
	{
		printf("No such file or directory\n");
		return (1);
	}
	return (0);
}
