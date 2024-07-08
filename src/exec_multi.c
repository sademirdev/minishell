#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

static void	close_other_fds(int i, int **fd, int arr_len, char *delete_me_on_release)
{
	int	j;

	j = 0;
	while (j < arr_len - 1)
	{
		if (j != i - 1 && j != i)
		{
			close(fd[i][0]);
			print_close(__func__, delete_me_on_release, i, 0);
			close(fd[i][1]);
			print_close(__func__, delete_me_on_release, i, 1);
		}
		j++;
	}
}

static void	set_fds(int **fd, t_cmd *cmd, int arr_len, int i, char *delete_me_on_release)
{
	if (cmd->in == NAFD)
		cmd->in = cmd->heredoc[i];
	if (i != 0)
	{
		close(fd[i - 1][1]);
		print_close(__func__, delete_me_on_release, i - 1, 1);
		if (cmd->in != NAFD)
		{
			dup2(cmd->in, STDIN_FILENO);
			close(fd[i - 1][0]);
			print_close(__func__, delete_me_on_release, i - 1, 0);
		}
		else
			dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
		dup2(cmd->in, STDIN_FILENO);
	if (i != arr_len - 1)
	{
		close(fd[i][0]);
		print_close(__func__, delete_me_on_release, i, 0);
		if (cmd->out != NAFD)
		{
			dup2(cmd->out, STDOUT_FILENO);
			close(fd[i][1]);
			print_close(__func__, delete_me_on_release, i, 1);
		}
		else
			dup2(fd[i][1], STDOUT_FILENO);
	}
	else
		dup2(cmd->out, STDOUT_FILENO);
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
	if (set_cmd_arg_and_path(state->token_arr[i], state, cmd) != SUCCESS)
		return (exit(state->status));
	print_debug(__func__, "Heredoc has been set.", cmd, arr_len, fd);
	close_other_fds(i, fd, arr_len, cmd->cmd);
	set_fds(fd, cmd, arr_len, i, cmd->cmd);
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

int	**pipe_fds_dispose_idx(int **pipe_fds, int i)
{
	if (!pipe_fds)
		return (NULL);
	if (i < 1)
		return (free(pipe_fds), NULL);
	while (i)
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
