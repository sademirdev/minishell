#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

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

static void	set_fds_1(int **fd, t_cmd *cmd, int i)
{
	if (fd)
	{
		if (i != 0)
		{
			close(fd[i - 1][1]);
			if (cmd->in != NAFD)
			{
				cmd->bin = cmd->in;
				close(fd[i - 1][0]);
			}
			else
				cmd->bin = fd[i - 1][0];
		}
		else
		{
			if (cmd->in != NAFD)
				cmd->bin = cmd->in;
			else
				cmd->bin = STDIN_FILENO;
		}
	}
	else
		if (cmd->in == NAFD)
			cmd->bin = STDIN_FILENO;
}

static void	set_fds_2(int **fd, t_cmd *cmd, int arr_len, int i)
{
	if (fd)
	{
		if (i != arr_len - 1)
		{
			close(fd[i][0]);
			if (cmd->out != NAFD)
			{
				cmd->bout = cmd->out;
				close(fd[i][1]);
			}
			else
				cmd->bout = fd[i][1];
		}
		else
		{
			if (cmd->out != NAFD)
				cmd->bout = cmd->out;
			else
				cmd->bout = STDOUT_FILENO;
		}
	}
	else
		if (cmd->out == NAFD)
			cmd->bout = STDOUT_FILENO;
}

void	built_in_handle_fds(t_cmd *cmd, int **pipe_fds)
{
	if (cmd->in == NAFD)
		if (cmd->heredoc)
			cmd->in = cmd->heredoc[cmd->idx];
	set_fds_1(pipe_fds, cmd, cmd->idx);
	set_fds_2(pipe_fds, cmd, cmd->count, cmd->idx);
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
		return (exec_pwd(cmd, state));
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
