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

int64_t	pipe_single_exec(t_token *token, t_state *state)
{
	int			pid;
	t_cmd		*cmd;

	if (!token || !state)
		return (FAILURE);

	cmd = token_to_cmd(token, state);
	if (!cmd)
		return (FAILURE);
	if (!is_built_in(token))
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
		if (pid == 0)
		{
			if (execve(cmd->cmd, cmd->argv, state->env) == -1)
				exit(1); // todo(sademir): handle error case
		}
	}
	else
	{
		if (execve(cmd->cmd, cmd->argv, state->env) == -1)
			return (FAILURE);
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

static void	handle_child_process(t_pipe_exec_metadata *md)
{
	int64_t	j;
	t_cmd	*cmd;

	j = 0;
	while (j < md->arr_len - 1)
	{
		if (j != md->i - 1 && j != md->i)
		{
			close(md->fd[j][0]);
			close(md->fd[j][1]);
		}
		j++;
	}
	if (md->i != 0)
	{
		close(md->fd[md->i - 1][1]);
		dup2(md->fd[md->i - 1][0], STDIN_FILENO);
	}
	if (md->i != md->arr_len - 1)
	{
		close(md->fd[md->i][0]);
		dup2(md->fd[md->i][1], STDOUT_FILENO);
	}
	cmd = token_to_cmd(md->token_arr[md->i], md->state);
	if (!cmd)
	{
		printf("cmd is null\n");
		exit(1); // todo(sademir): handle error case
	}
	if (execve(cmd->cmd, cmd->argv, md->state->env) == -1)
	{
		printf("execve\n");
		exit(1); // todo(sademir): handle error case
	}
}

int64_t	fork_init(t_pipe_exec_metadata* md)
{
	pid_t	pid;

	md->i = 0;
	if (!md->fd || md->arr_len < 0)
		return (FAILURE);
	while (md->i < md->arr_len)
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
		if (pid == 0)
			handle_child_process(md);
		else
		{
			if (md->i != 0)
			{
				close(md->fd[md->i - 1][0]);
				close(md->fd[md->i - 1][1]);
			}
		}
		md->i++;
	}
	return (SUCCESS);
}

int64_t	pipe_exec(t_token **token_arr, t_state *state)
{
	t_pipe_exec_metadata	md;

	if (!token_arr || !state)
		return (FAILURE);
	md.arr_len = token_arr_len(token_arr);
	if (md.arr_len < 1)
		return (FAILURE);
	if (md.arr_len == 1)
		return (pipe_single_exec(token_arr[0], state));
	md.fd = (int (*)[2]) malloc(sizeof(int [2]) * (md.arr_len - 1));
	if (!md.fd)
		return (FAILURE);
	if (pipe_init(md.fd, md.arr_len - 1) != SUCCESS)
		return (FAILURE);
	if (fork_init(&md) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
