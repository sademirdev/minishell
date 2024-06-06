#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_env_path(char **env)
{
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (ft_substr(env[i], 5, ft_strlen(env[i]) - 5));
		i++;
	}
	return (NULL);
}

void	dispose_paths(char **paths)
{
	int	i;

	if (!paths)
		return ;
	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char *join_path(char **paths, char *command)
{
	char	*cmd_path;
	char	*tmp;
	int		i;

	if (!paths || !command)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/", false);
		if (!tmp)
			return (dispose_paths(paths), NULL);
		cmd_path = ft_strjoin(tmp, command, false);
		if (!cmd_path)
			return (dispose_paths(paths), NULL);
		if (access(cmd_path, X_OK) == 0)
			return (dispose_paths(paths), cmd_path);
		free(cmd_path);
		i++;
	}
	return (command);
}

char	*find_path(char *command, char **env)
{
	char	**paths;
	char	*path;

	if (!command)
		return (NULL);
	path = get_env_path(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	free(path);
	return (join_path(paths, command));
}
