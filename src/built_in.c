#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static bool	str_is_build_in(const char *str)
{
	if (!str)
		return (false);
	if (ft_strncmp(str, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(str, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(str, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(str, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(str, "exit", 5) == 0)
		return (true);
	return (false);
}

static int	set_built_in_path_and_arg(t_state *state, t_token *token, t_cmd *cmd)
{
	char	*cmd_path;
	char	**argv;

	cmd_path = token->data;
	if (!cmd_path)
	{
		if (state->err != HANDLED)
			return (print_exec_err(state, token, 127, ERR_CMD_NOT_FOUND), FAILURE);
		return (FAILURE);
	}
	cmd->cmd = cmd_path;
	argv = token_to_arg(token, cmd_path);
	if (!argv)
		return (free(cmd_path), FAILURE);
	cmd->argv = argv;
	return (SUCCESS);
}
void	built_in_handle_fds(t_cmd *cmd, int **pipe_fds)
{
	if (pipe_fds)
	{
		if (cmd->idx < cmd->count - 1 && cmd->idx != 0 && cmd->in == NAFD)
			cmd->bin = pipe_fds[cmd->idx][0];
		else if (cmd->in != NAFD)
			cmd->bin = cmd->in;
		if (cmd->idx < cmd->count - 1 && cmd->out == NAFD)
			cmd->bout = pipe_fds[cmd->idx][1];
		else if (cmd->out != NAFD)
			cmd->bout = cmd->out;
	}
	if (cmd->in == NAFD)
		cmd->bin = STDIN_FILENO;
	if (cmd->out == NAFD)
		cmd->bout = STDOUT_FILENO;
}

int	exec_built_in(t_state *state, t_token *token, t_cmd *cmd, int **pipe_fds)
{
	built_in_handle_fds(cmd, pipe_fds);
	if (set_built_in_path_and_arg(state, token, cmd) != SUCCESS)
		return (FAILURE);
	if (ft_strncmp(token->data, "echo", 5) == 0)
		return (exec_echo(state, token, cmd));
	if (ft_strncmp(token->data, "cd", 3) == 0)
		return (exec_cd(state, token));
	if (ft_strncmp(token->data, "pwd", 4) == 0)
		return (exec_pwd(cmd));
	if (ft_strncmp(token->data, "export", 7) == 0)
		return (exec_export(state, token, cmd));
	if (ft_strncmp(token->data, "unset", 6) == 0)
		return (exec_unset(state, token));
	if (ft_strncmp(token->data, "env", 4) == 0)
		return (exec_env(state, cmd));
	if (ft_strncmp(token->data, "exit", 5) == 0)
		return (exec_exit(state, token));
	return (SUCCESS);
}

bool	cmd_is_str_built_in(t_cmd *cmd)
{
	if (!cmd || !cmd->cmd)
		return (false);
	return (str_is_build_in(cmd->cmd));
}

bool	token_is_built_in(t_token *token)
{
	if (!token || token->type != CMD)
		return (false);
	return (str_is_build_in(token->data));
}
