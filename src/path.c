#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

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

char	*get_cmd_absolute_path(t_token *token, t_state *state)
{
	struct stat	buf;
	char		*new;

	stat(token->data, &buf);
	if (errno == EACCES)
		return (print_exec_err(state, token, 106, EACCES), NULL);
	if (S_ISDIR(buf.st_mode))
		return (print_exec_err(state, token, 126, ERR_IS_DIR), NULL);
	if (access(token->data, F_OK))
		return (print_exec_err(state, token, 127, \
			ERR_NO_SUCH_FILE_OR_DIR), NULL);
	if (access(token->data, X_OK))
		return (print_exec_err(state, token, 126, ERR_PERMISSION_DENIED), NULL);
	new = ft_strdup(token->data);
	if (!new)
		return (NULL);
	return (new);
}

static char	*get_cmd_relative_path(t_token *token, t_state *state, char **path_arr)
{
	char			*cmd_path;
	char			*temp;
	int				i;
	struct stat		buf;

	i = 0;
	if (*token->data == '\0')
		return (print_exec_err(state, token, 127, ERR_CMD_NOT_FOUND), NULL);
	while (path_arr[i])
	{
		temp = ft_strjoin(path_arr[i++], "/", false);
		if (!temp)
			return (NULL);
		while (token->type != CMD)
			token = token->next;
		cmd_path = ft_strjoin(temp, token->data, true);
		if (!cmd_path)
			return (NULL);
		stat(cmd_path, &buf);
		if (S_ISDIR(buf.st_mode))
			return (free(cmd_path), print_exec_err(state, token, 127, ERR_IS_DIR), NULL);
		if (!access(cmd_path, F_OK) && !access(cmd_path, X_OK))
			return (cmd_path);
		free(cmd_path);
	}
	if (token_is_built_in(token))
		return (token->data);
	return (print_exec_err(state, token, 127, ERR_CMD_NOT_FOUND), NULL);
}

char	*get_cmd_path(t_token *token, t_state *state)
{
	char	*path_arr_str;
	char	**path_arr;
	char	*rsp;

	if (ft_strchr(token->data, '/'))
		return (get_cmd_absolute_path(token, state));
	if (!state->env)
		return (print_exec_err(state, token, 127, ERR_CMD_NOT_FOUND), NULL);
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
