#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

static bool	is_built_in(t_token *token)
{
	if (!token || token->type != CMD)
		return (false);
	if (ft_strncmp(token->data, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(token->data, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(token->data, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(token->data, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(token->data, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(token->data, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(token->data, "exit", 4) == 0)
		return (true);
	return (false);
}

int64_t	pipe_single_exec(t_token *token, t_state *state, t_cmd *cmd)
{
	int			pid;

	if (!token || !state || !cmd)
		return (FAILURE);
	set_red_file_fds(token, cmd);
	set_cmd_arg_and_path(token, state, cmd);
	if (!is_built_in(token))
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
		if (pid == 0)
		{
			if (cmd->in != -2)
				dup2(cmd->in, STDIN_FILENO);
			cmd->cmd = "/bin/`cat";
			if (execve(cmd->cmd, cmd->argv, state->env) == -1)
				exit(1); // todo(sademir): handle error case
		}
		else
			wait(NULL);
	}
	else
	{
		// todo(sademir): add build in exec
	}
	return (SUCCESS);
}

int64_t	pipe_init(int (*fd)[2], int64_t pipe_count)
{
	int64_t	i;

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
	int64_t	j;
	int64_t	arr_len;

	arr_len = token_arr_len(token_arr);
	if (!token_arr[i] || !state || arr_len < 1 || !cmd)
		exit(1); // todo(sademir): handle error case
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
	if (i != 0)
	{
		close(fd[i - 1][1]);
		if (cmd->in == -2)
			dup2(fd[i - 1][0], STDIN_FILENO);
		else
			dup2(cmd->in, STDIN_FILENO);
	}
	if (i != arr_len - 1)
	{
		close(fd[i][0]);
		if (cmd->out == -2)
			dup2(fd[i][1], STDOUT_FILENO);
		else
			dup2(cmd->out, STDOUT_FILENO);
	}
	if (execve(cmd->cmd, cmd->argv, state->env) == -1)
	{
		printf("execve\n");
		exit(1); // todo(sademir): handle error case
	}
}

int64_t	fork_init(int (*fd)[2], int64_t arr_len, t_token **token_arr, t_state *state, t_cmd *cmd)
{
	int64_t	i;
	pid_t	pid;

	i = 0;
	if (!fd || arr_len < 0)
		return (FAILURE);
	while (i < arr_len)
	{
		set_red_file_fds(token_arr[i], cmd);
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
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
	wait(NULL);
	return (SUCCESS);
}

int64_t	pipe_exec(t_token **token_arr, t_state *state)
{
	int64_t	arr_len;
	int		(*fd)[2];
	t_cmd	cmd;

	// todo(sademir): check in out values
	cmd.argv = NULL;
	cmd.cmd = NULL;
	cmd.in = -2;
	cmd.out = -2;
	if (!token_arr || !state)
		return (FAILURE);
	arr_len = token_arr_len(token_arr);
	if (arr_len < 1)
		return (FAILURE);
	if (arr_len == 1)
		return (pipe_single_exec(token_arr[0], state, &cmd));
	fd = (int (*)[2]) malloc(sizeof(int [2]) * (arr_len - 1));
	if (!fd)
		return (FAILURE);
	if (pipe_init(fd, arr_len - 1) != SUCCESS)
		return (FAILURE);
	if (fork_init(fd, arr_len, token_arr, state, &cmd) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
