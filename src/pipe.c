#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>

int64_t	pipe_single_exec(t_token *token_arr, t_state *state)
{
	return (1);
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

int64_t	fork_init(int (*fd)[2], int64_t arr_len, t_token **token_arr, t_state *state)
{
	int64_t	i;
	int			pid;
	t_cmd		*cmd;

	i = 0;
	if (!fd || arr_len < 0)
		return (FAILURE);
	while (i < arr_len)
	{
		pid = fork();
		if (pid == -1)
			return (FAILURE); // todo(kkarakus): handle close;
		if (pid == 0)
		{
			if (i != 0)
				dup2(fd[i - 1][0], STDIN_FILENO);
			if (i != arr_len - 1)
				dup2(fd[i][1], STDOUT_FILENO);
			cmd = token_to_cmd(token_arr[i], state);
			if (!cmd)
				exit(1); // todo(sademir): handle error case
			if (execve(cmd->cmd, cmd->argv, state->env) == -1)
				exit(1); // todo(sademir): handle error case
			break ;
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
