#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>

static int	w_exit_status(int status)
{
	return ((status >> 8) & 0x000000ff);
}

// void	handle_exec_error(t_token *token, t_cmd *cmd)
// {
// 	struct stat	buf;

// 	stat(token->data, &buf);
// 	if (!S_ISDIR(buf.st_mode) && ft_strncmp(cmd->cmd, token->data, ft_strlen(cmd->cmd) + 1) == 0)
// 	{
// 		print_err(cmd->cmd, ERR_CMD_NOT_FOUND);
// 		exit(127);
// 	}
//  	else if (S_ISDIR(buf.st_mode))
// 	{
// 		print_err(cmd->cmd, EISDIR);
// 		exit(126);
// 	}
// 	else if (errno == EACCES || access(token->data, X_OK))
// 	{
// 		print_err(cmd->cmd, EACCES);
// 		exit(126);
// 	}
// 	else if (access(token->data, F_OK))
// 	{
// 		print_err(cmd->cmd, ENOENT);
// 		exit(127);
// 	}
// 	else
// 	{
// 		print_err(cmd->cmd, errno);
// 		exit(127);
// 	}
// }

int	pipe_single_exec(t_token *token, t_state *state, t_cmd *cmd)
{
	int			pid;

	if (!token || !state || !cmd)
		return (FAILURE);
	if (set_heredoc_fds(token, cmd, 0) != SUCCESS)
		return (FAILURE);
	if (set_red_file_fds(token, cmd, state) != SUCCESS)
		return (FAILURE);
	if (set_cmd_arg_and_path(token, state, cmd) != SUCCESS)
		return (FAILURE);
	if (!cmd->cmd)
		return (FAILURE);
	if (cmd->in == NAFD)
		cmd->in = cmd->heredoc[0];
	if (token_is_built_in(token))
	{
		if (handle_built_in(token, state, cmd) != SUCCESS)
			return (FAILURE);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
		else if (pid == 0)
		{
			if (cmd->in != NAFD)
				dup2(cmd->in, STDIN_FILENO);
			if (cmd->out != NAFD)
				dup2(cmd->out, STDOUT_FILENO);
			if (execve(cmd->cmd, cmd->argv, state->env) == -1)
				exit(state->status);
		}
		if (pid != 0)
		{
			waitpid(pid, &state->status, 0);
			state->status = w_exit_status(state->status);
		}
	}
	if (cmd)
	{
		if (cmd->argv)
		{
			free(cmd->heredoc);
			cmd->heredoc = NULL;
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

static int	handle_child_process(t_token **token_arr, t_state *state, int i, int (*fd)[2], t_cmd *cmd)
{
	int	j;
	int	arr_len;

	arr_len = token_arr_len(token_arr);
	if (!token_arr[i] || !state || arr_len < 1 || !cmd)
		return (FAILURE);
	if (set_red_file_fds(token_arr[i], cmd, state) != SUCCESS)
		return (FAILURE);
	if (set_cmd_arg_and_path(token_arr[i], state, cmd) != SUCCESS)
		return (FAILURE);
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
	if (cmd_is_str_built_in(cmd))
		return (handle_built_in(token_arr[i], state, cmd));
	else if (execve(cmd->cmd, cmd->argv, state->env) == -1)
		exit(state->status);
	return (SUCCESS);
}

int	fork_init(int (*fd)[2], int arr_len, t_token **token_arr, t_state *state, t_cmd *cmd)
{
	pid_t	*pids;
	pid_t	pid;
	int		i;

	i = 0;
	if (!fd || arr_len < 0)
		return (FAILURE);
	pids = (int *) malloc(sizeof(int) * (arr_len + 1));
	if (!pids)
		return (FAILURE);
	while (i < arr_len)
	{
		if (set_heredoc_fds(token_arr[i], cmd, i) != SUCCESS)
			return (FAILURE);
		pid = fork();
		if (pid == -1)
			return (free(pids), FAILURE);
		pids[i] = pid;
		if (pid == 0)
		{
			if (handle_child_process(token_arr, state, i, fd, cmd) != SUCCESS)
				exit(state->status);
			else
				exit(0);
		}
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
	i = 0;
	while (i < arr_len)
	{
		waitpid(pids[i], &state->status, 0);
		state->status = w_exit_status(state->status);
		i++;
	}
	return (free(pids), SUCCESS);
}

int	cmd_init(t_cmd *cmd, int arr_len)
{
	int32_t	i;

	cmd->argv = NULL;
	cmd->cmd = NULL;
	cmd->in = NAFD;
	cmd->out = NAFD;
	cmd->heredoc = (int *) malloc(sizeof(int) * arr_len);
	if (!cmd->heredoc)
		return (FAILURE);
	i = 0;
	while (i < arr_len)
	{
		cmd->heredoc[i] = NAFD;
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
		return (FAILURE);
	arr_len = token_arr_len(state->token_arr);
	if (arr_len < 1)
		return (FAILURE);
	if (cmd_init(&cmd, arr_len) != SUCCESS)
		return (FAILURE);
	if (arr_len == 1)
		return (pipe_single_exec(state->token_arr[0], state, &cmd));
	fd = (int (*)[2]) malloc(sizeof(int [2]) * (arr_len - 1));
	if (!fd)
		return (free(cmd.heredoc), FAILURE);
	if (pipe_init(fd, arr_len - 1) != SUCCESS)
		return (free(fd), free(cmd.heredoc), FAILURE);
	if (fork_init(fd, arr_len, state->token_arr, state, &cmd) != SUCCESS)
		return (free(fd), free(cmd.heredoc), FAILURE);
	return (SUCCESS);
}
