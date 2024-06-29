#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static bool	is_relative_path(const char *path);
static bool	is_absolute_path(const char *path);
static int	handle_relative_path(t_token *token, t_state *state);
static int	handle_absolute_path(t_token *token, t_state *state);

int	handle_cd(t_token *token, t_state *state)
{
	const char	*home_path;

	if (!token)
		return (FAILURE);
	home_path = getenv("HOME");
	if (!home_path)
		return (print_exec_err(state, token, 113, ERR_HOME_NOT_SET));
	if (!token->next)
	{
		if (chdir(home_path) == -1)
			return (print_exec_err(state, token, 114, ERR_CANT_CHANGE_DIR));
		return (SUCCESS);
	}
	if (is_relative_path(token->next->data))
		return (handle_relative_path(token, state));
	else if (is_absolute_path(token->next->data))
		return (handle_absolute_path(token, state));
	return (FAILURE);
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

static int	handle_relative_path(t_token *token, t_state *state)
{
	char	*temp_path;
	char	cwd[PATH_MAX];
	int		len;

	len = 0;
	if (!getcwd(cwd, PATH_MAX))
		return (FAILURE);
	len = ft_strlen(cwd) + ft_strlen(token->next->data) + 1;
	if (len >= PATH_MAX)
		return (FAILURE);
	temp_path = malloc(sizeof(char) * (len + 1));
	if (!temp_path)
		return (FAILURE);
	ft_strlcpy(temp_path, cwd, ft_strlen(cwd) + 1);
	temp_path[ft_strlen(cwd)] = '/';
	ft_strlcpy(temp_path + ft_strlen(cwd) + 1, token->next->data, len);
	temp_path[len] = '\0';
	if (chdir(temp_path) == -1)
		return (free(temp_path), print_exec_err(state, token, 1, ERR_NO_SUCH_FILE_OR_DIR));
	return (free(temp_path), SUCCESS);
}

static int	handle_absolute_path(t_token *token, t_state *state)
{
	if (chdir(token->next->data) == -1)
		return (print_exec_err(state, token, 120, ERR_CANT_CHANGE_DIR));
	return (SUCCESS);
}
