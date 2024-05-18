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

static void	handle_child_process(t_token **token_arr, t_state *state, int i, int (*fd)[2])
{
	int64_t	j;
	int64_t	arr_len;
	t_cmd	*cmd;

	arr_len = token_arr_len(token_arr);
	if (!token_arr[i] || !state || arr_len < 1)
		exit(1); // todo(sademir): handle error case
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
		dup2(fd[i - 1][0], STDIN_FILENO);
	}
	if (i != arr_len - 1)
	{
		close(fd[i][0]);
		dup2(fd[i][1], STDOUT_FILENO);
	}
	cmd = token_to_cmd(token_arr[i], state);
	if (!cmd)
	{
		printf("cmd is null\n");
		exit(1); // todo(sademir): handle error case
	}
	if (execve(cmd->cmd, cmd->argv, state->env) == -1)
	{
		printf("execve\n");
		exit(1); // todo(sademir): handle error case
	}
}

int64_t	fork_init(int (*fd)[2], int64_t arr_len, t_token **token_arr, t_state *state)
{
	int64_t	i;
	pid_t	pid;

	i = 0;
	if (!fd || arr_len < 0)
		return (FAILURE);
	while (i < arr_len)
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
		if (pid == 0)
			handle_child_process(token_arr, state, i, fd);
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
	return (SUCCESS);
}

int64_t	pipe_exec(t_token **token_arr, t_state *state)
{
	int64_t	arr_len;
	int		(*fd)[2];

	if (!token_arr || !state)
		return (FAILURE);
	arr_len = token_arr_len(token_arr);
	if (arr_len < 1)
		return (FAILURE);
	if (arr_len == 1)
		return (pipe_single_exec(token_arr[0], state));
	fd = (int (*)[2]) malloc(sizeof(int [2]) * (arr_len - 1));
	if (!fd)
		return (FAILURE);
	if (pipe_init(fd, arr_len - 1) != SUCCESS)
		return (FAILURE);
	if (fork_init(fd, arr_len, token_arr, state) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
