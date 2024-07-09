#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

// + echo a > a | echo b > b | echo c > c | echo d > d
// + echo a | echo b | echo c | echo d
// ls -la | grep c | wc -l
// cat << a | cat << b | cat << c

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
		{
			cmd->in = cmd->heredoc[i];
		}
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
			dup2(fd[i][1], STDOUT_FILENO);
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

int	**pipe_fds_dispose_idx(int **pipe_fds, int i)
{
	if (!pipe_fds)
		return (NULL);
	if (i < 1)
		return (free(pipe_fds), NULL);
	i--;
	while (i >= 0)
	{
		free(pipe_fds[i]);
		i--;
	}
	return (NULL);
}

int	**pipe_fds_init(int pipe_count)
{
	int	**pipe_fds;
	int	i;

	pipe_fds = (int **) malloc(sizeof(int *) * pipe_count);
	if (!pipe_fds)
		return (NULL);
	i = 0;
	while (i < pipe_count)
	{
		pipe_fds[i] = (int *) malloc(sizeof(int) * 2);
		if (!pipe_fds[i])
			return (pipe_fds_dispose_idx(pipe_fds, i));
		i++;
	}
	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipe_fds[i]) == -1)
			return (pipe_fds_dispose_idx(pipe_fds, pipe_count - 1), NULL);
		i++;
	}
	return (pipe_fds);
}
