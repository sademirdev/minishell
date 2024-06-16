#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static int	w_exit_status(int status)
{
	return ((status >> 8) & 0x000000ff);
}

int	pipe_single_exec(t_token *token, t_state *state, t_cmd *cmd)
{
	int			pid;

	if (!token || !state || !cmd)
		return (FAILURE);
	set_heredoc_fds(token, cmd, 0);
	if (set_red_file_fds(token, cmd, state) == 1)
		return (1);	
	set_cmd_arg_and_path(token, state, cmd);
	if (!cmd->cmd)
		return (1);
	if (cmd->in == -2)
		cmd->in = cmd->heredoc[0];
	if (!is_built_in(token))
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
		if (pid == 0)
		{
			if (cmd->in != -2)
				dup2(cmd->in, STDIN_FILENO);
			if (cmd->out != -2)
				dup2(cmd->out, STDOUT_FILENO);
			if (execve(cmd->cmd, cmd->argv, state->env) == -1)
			{
				print_err(cmd->cmd, ERR_CMD_NOT_FOUND);
				exit(127); // todo(sademir): handle error case
			}
		}
		if (pid != 0)
		{
			waitpid(pid, &state->status, 0);
			state->status = w_exit_status(state->status);
		}
	}
	else
		handle_built_in(token, state, cmd);
	if (cmd)
	{
		if (cmd->argv)
		{
			free(cmd->heredoc);
			cmd->heredoc = NULL;
			// free(cmd->argv[0]); //todo(sademir): if it is open, it gives double free error (prompt = ca)
			// cmd->argv[0] = NULL;
			free(cmd->argv);
			cmd->argv = NULL;
			return (SUCCESS);
		}
		return (free(cmd->heredoc), SUCCESS);
	}
	return (SUCCESS);
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

static void	handle_child_process(t_token **token_arr, t_state *state, int i, int (*fd)[2], t_cmd *cmd)
{
	int	j;
	int	arr_len;

	arr_len = token_arr_len(token_arr);
	if (!token_arr[i] || !state || arr_len < 1 || !cmd)
		exit(1); // todo(sademir): handle error case
	if (set_red_file_fds(token_arr[i], cmd, state) == 1)
	{
		state->status = 1;
		exit (1);
	}
	set_cmd_arg_and_path(token_arr[i], state, cmd);
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
	if (cmd->in == -2)
		cmd->in = cmd->heredoc[i];
	if (i != 0)
	{
		close(fd[i - 1][1]);
		if (cmd->in != -2)
			dup2(cmd->in, STDIN_FILENO);
		else
			dup2(fd[i - 1][0], STDIN_FILENO);
	}
	else
		dup2(cmd->in, STDIN_FILENO);
	if (i != arr_len - 1)
	{
		close(fd[i][0]);
		if (cmd->out != -2)
			dup2(cmd->out, STDOUT_FILENO);
		else
			dup2(fd[i][1], STDOUT_FILENO);
	}
	else
		dup2(cmd->out, STDOUT_FILENO);
	if (execve(cmd->cmd, cmd->argv, state->env) == -1)
	{
		print_err(cmd->cmd, ERR_FILE_NOT_FOUND);
		exit(127); // todo(sademir): handle error case
	}
}

int	fork_init(int (*fd)[2], int arr_len, t_token **token_arr, t_state *state, t_cmd *cmd)
{
	int	i;
	pid_t	pid;
	pid_t	*pids;

	i = 0;
	if (!fd || arr_len < 0)
		return (FAILURE);
	pids = (int *) malloc(sizeof(int) * (arr_len + 1));
	if (!pids)
		return (FAILURE);
	while (i < arr_len)
	{
		set_heredoc_fds(token_arr[i], cmd, i);
		pid = fork();
		pids[i] = pid;
		if (pid == -1)
			return (free(pids), FAILURE); // todo(kkarakus): handle close;
		if (pid == 0)
			handle_child_process(token_arr, state, i, fd, cmd);
		else
		{
			if (i != 0)
			{
				close(fd[i - 1][0]);
				close(fd[i - 1][1]);
			}
		}
		i++;
	}
	i = arr_len - 1;
	while (i >= 0)
	{
		waitpid(pids[i], &state->status, 0);
		state->status = w_exit_status(state->status);
		i--;
	}
	return (free(pids), SUCCESS);
}

int	cmd_init(t_cmd *cmd, int arr_len)
{
	int32_t	i;

	cmd->argv = NULL;
	cmd->cmd = NULL;
	cmd->in = -2;
	cmd->out = -2;
	cmd->heredoc = (int *)malloc(sizeof(int) * arr_len);
	if (!cmd->heredoc)
		return (FAILURE);
	i = 0;
	while (i < arr_len)
	{
		cmd->heredoc[i] = -2;
		i++;
	}
	return (SUCCESS);
}

int	execute_prompt(t_state *state)
{
	int		arr_len;
	t_cmd	cmd;
	int		(*fd)[2];
	
	if (!state || !state->token_arr)
		return (1);
	arr_len = token_arr_len(state->token_arr);
	if (arr_len < 1)
		return (FAILURE);
	if (cmd_init(&cmd, arr_len) != 0)
		return (FAILURE);
	if (arr_len == 1)
		return (pipe_single_exec(state->token_arr[0], state, &cmd));
	fd = (int (*)[2]) malloc(sizeof(int [2]) * (arr_len - 1));
	if (!fd)
		return (free(cmd.heredoc), 1);
	if (pipe_init(fd, arr_len - 1) != 0)
		return (free(fd), free(cmd.heredoc), 1);
	if (fork_init(fd, arr_len, state->token_arr, state, &cmd) != 0)
		return (free(fd), free(cmd.heredoc), 1);
	return (0);
}
