#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static void	close_other_fds(int i, int (*fd)[2], int arr_len)
{
	int	j;

	j = 0;
	i++;
	while (j < arr_len - 1)
	{
		if (j != i - 1 && j != i)
		{
			close(fd[i][0]);
			close(fd[i][1]);
		}
		j++;
	}
}

static void	set_fds(int (*fd)[2], t_cmd *cmd, int arr_len, int i)
{
	if (cmd->in == NAFD)
		cmd->in = cmd->heredoc[i];
	if (i != 0)
	{
		close(fd[i - 1][1]);
		if (cmd->in != NAFD)
			dup2(cmd->in, STDIN_FILENO);
		else
			dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
		dup2(cmd->in, STDIN_FILENO);
	if (i != arr_len - 1)
	{
		close(fd[i][0]);
		if (cmd->out != NAFD)
			dup2(cmd->out, STDOUT_FILENO);
		else
			dup2(fd[i][1], STDOUT_FILENO);
	}
	else
		dup2(cmd->out, STDOUT_FILENO);
}

void	handle_child_process(int (*fd)[2], t_state *state, t_cmd *cmd, int i)
{
	int	arr_len;

	arr_len = token_arr_len(state->token_arr);
	if (!state->token_arr[i] || !state || arr_len < 1 || !cmd)
		return (exit(state->status));
	if (set_red_file_fds(state->token_arr[i], cmd, state) != SUCCESS)
		return (exit(state->status));
	if (set_cmd_arg_and_path(state->token_arr[i], state, cmd) != SUCCESS)
		return (exit(state->status));
	close_other_fds(i, fd, arr_len);
	set_fds(fd, cmd, arr_len, i);
	if (cmd_is_str_built_in(cmd))
	{
		if (exec_built_in(state, state->token_arr[i], cmd) != SUCCESS)
			return (exit(state->status));
		exit(0);
	}
	else if (execve(cmd->cmd, cmd->argv, state->env) == -1)
		exit(state->status);
	exit(0);
}

int	pipe_init(int (*fd)[2], int pipe_count)
{
	int	i;

	if (!fd)
		return (FAILURE);
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(fd[i]) == -1)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}
