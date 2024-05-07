#include "minishell.h"
#include <unistd.h>

bool	has_path(char *envp[])
{
	int64_t	i;

	if (!envp)
		return (false);
	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH", 4))
			return (true);
		i++;
	}
	return (false);
}

char	*get_path(char *envp[])
{
	int64_t	i;
	char		*path;

	if (!has_path(envp))
		return (NULL);
	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	return (path);
}

char	*find_path(char *command, char *envp[])
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	paths = ft_split(ft_path(envp), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		if (access(path, X_OK) == 0)
			return (path);
		free(tmp);
		i++;
	}
	return (NULL);
}
