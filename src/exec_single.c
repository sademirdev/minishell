#include "minishell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	exec_single_cmd_with_fork(t_cmd *cmd, t_state *state)
{
	pid_t	pid;

	g_sig = 1;
	pid = fork();
	if (pid == -1)
		return (FAILURE);
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
	g_sig = 0;
	return (SUCCESS);
}

int	exec_single_cmd_prepare_fds(t_token *token, t_state *state, t_cmd *cmd)
{
	if (set_heredoc_fds(token, cmd, 0) != SUCCESS)
		return (FAILURE);
	if (set_red_file_fds(token, cmd, state) != SUCCESS)
		return (FAILURE);
	if (token_has_cmd(token) == false)
		return (SUCCESS);
	if (set_cmd_arg_and_path(token, state, cmd, NULL) != SUCCESS)
		return (FAILURE);
	if (!cmd->cmd)
		return (FAILURE);
	if (cmd->in == NAFD)
		cmd->in = cmd->heredoc[0];
	return (SUCCESS);
}

void	cmd_dispose(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->cmd);
	cmd->cmd = NULL;
	free(cmd->argv);
	cmd->argv = NULL;
	free(cmd->heredoc);
	cmd->heredoc = NULL;
}

int	exec_single_cmd(t_token *token, t_state *state, t_cmd *cmd)
{
	if (!token || !state || !cmd)
		return (FAILURE);
	if (exec_single_cmd_prepare_fds(token, state, cmd) != SUCCESS)
		return (cmd_dispose(cmd), FAILURE);
	if (exec_single_cmd_with_fork(cmd, state) != SUCCESS)
		return (cmd_dispose(cmd), FAILURE);
	return (cmd_dispose(cmd), SUCCESS);
}
