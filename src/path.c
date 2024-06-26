#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

char	*get_env_path_arr_as_str(char **env)
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
	char	*temp;
	int		i;

	if (!paths || !command)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/", false);
		if (!temp)
			return (dispose_paths(paths), NULL);
		cmd_path = ft_strjoin(temp, command, false);
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

	if (!command || command[0] == '\0')
		return (NULL);
	path = get_env_path_arr_as_str(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	free(path);
	return (join_path(paths, command));
}

char	*get_cmd_absolute_path(t_token *token, t_state *state)
{
	struct stat	buf;

	stat(token->data, &buf);
	if (errno == EACCES)
		return (print_exec_err(state, token, 106, EACCES), NULL);
	if (S_ISDIR(buf.st_mode))
		return (print_exec_err(state, token, 107, EISDIR), NULL);
	if (access(token->data, F_OK))
		return (print_exec_err(state, token, 108, ENOENT), NULL);
	if (access(token->data, X_OK))
		return (print_exec_err(state, token, 109, EACCES), NULL);
	return (token->data);
}

char *get_cmd_relative_path(t_token *token, t_state *state, char **path_arr)
{
	struct stat	buf;
	char				*cmd_path;
	char				*temp;
	int					i;

	i = 0;
	while (path_arr[i])
	{
		temp = ft_strjoin(path_arr[i], "/", false);
		if (!temp)
			return (NULL);
		cmd_path = ft_strjoin(temp, token->data, false);
		if (!cmd_path)
			return (NULL);
		stat(cmd_path, &buf);
		if (S_ISDIR(buf.st_mode))
			return (print_exec_err(state, token, 110, EISDIR), NULL);
		if (!access(cmd_path, F_OK) && !access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (print_exec_err(state, token, 0, ERR_OTHER), NULL);
}

char	*get_cmd_path(t_token *token, t_state *state)
{
	char	*path_arr_str;
	char	**path_arr;
	char	*rsp;

	if (ft_strchr(token->data, '/'))
		return (get_cmd_absolute_path(token, state));
	path_arr_str = get_env_path_arr_as_str(state->env);
	if (!path_arr_str)
		return (NULL);
	path_arr = ft_split(path_arr_str, ':');
	if (!path_arr)
		return (NULL);
	free(path_arr_str);
	rsp = get_cmd_relative_path(token, state, path_arr);
	dispose_paths(path_arr);
	return (rsp);
}
