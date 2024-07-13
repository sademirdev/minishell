#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static void	close_other_fds(int i, int **fd, int arr_len)
{
	int	j;

	j = 0;
	while (j < arr_len - 1)
	{
		if (j != i - 1 && j != i)
		{
			close(fd[j][0]);
			close(fd[j][1]);
		}
		j++;
	}
}

static void	set_fds_1(int **fd, t_cmd *cmd, int i)
{
	if (cmd->in == NAFD)
	{
		if (cmd->heredoc)
			cmd->in = cmd->heredoc[i];
	}
	if (i != 0)
	{
		close(fd[i - 1][1]);
		if (cmd->in != NAFD)
		{
			dup2(cmd->in, STDIN_FILENO);
			close(fd[i - 1][0]);
		}
		else
			dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
	{
		if (cmd->in != NAFD)
			dup2(cmd->in, STDIN_FILENO);
	}
}

static void	set_fds_2(int **fd, t_cmd *cmd, int arr_len, int i)
{
	if (i != arr_len - 1)
	{
		close(fd[i][0]);
		if (cmd->out != NAFD)
		{
			dup2(cmd->out, STDOUT_FILENO);
			close(fd[i][1]);
		}
		else
		{
			dup2(fd[i][1], STDOUT_FILENO);
			close(fd[i][1]);
		}
	}
	else
	{
		if (cmd->out != NAFD)
			dup2(cmd->out, STDOUT_FILENO);
	}
}

void	handle_child_process(int **fd, t_state *state, t_cmd *cmd, int i)
{
	int	arr_len;

	arr_len = token_arr_len(state->token_arr);
	if (!state->token_arr[i] || !state || arr_len < 1 || !cmd)
		return (exit(state->status));
	if (set_red_file_fds(state->token_arr[i], cmd, state) != SUCCESS)
		return (exit(state->status));
	if (token_has_cmd(state->token_arr[i]) == false)
		return (exit(state->status));
	cmd->idx = i;
	cmd->count = arr_len;
	close_other_fds(i, fd, arr_len);
	if (set_cmd_arg_and_path(state->token_arr[i], state, cmd, fd) != SUCCESS)
		return (exit(state->status));
	set_fds_1(fd, cmd, i);
	set_fds_2(fd, cmd, arr_len, i);
	if (execve(cmd->cmd, cmd->argv, state->env) == -1)
		exit(state->status);
	exit(0);
}
