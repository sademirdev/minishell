#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	handle_redl(t_token *token, t_cmd *cmd, bool has_last_heredoc, t_state *state)
{
	t_token	*temp;

	if (!token)
		return (FAILURE);
	temp = token->next;
	if (temp && !temp->next && temp->prev && !temp->prev->prev)
		return (FAILURE);
	if (access(temp->data, F_OK) == -1)
	{
		state->status = 1;
		return (print_err(temp->data, ERR_FILE_NOT_FOUND), FAILURE);
	}
	if (access(temp->data, R_OK) == -1) // todo(apancar): check access()
	{
		state->status = 2;
		return (print_err(temp->data, ERR_FILE_PERMISSION_DENIED), FAILURE);
	}
	if (has_last_heredoc)
		close(open(temp->data, O_RDONLY));
	else
	{
		if (cmd->in != -2)
			close(cmd->in);
		cmd->in = open(temp->data, O_RDONLY);
	}
	if (cmd->in == -1)
		return (print_err(temp->data, ERR_FILE_OPEN), FAILURE);
	return (SUCCESS);
}

int	handle_redll(t_token *token, t_cmd *cmd, int i)
{
	t_token	*temp;
	char	*buf;
	int		fd[2];

	if (!token || !token->next)
		return (FAILURE);
	temp = token->next;
	if (pipe(fd) == -1)
		return (FAILURE);
	while (true)
	{
		buf = readline("> ");
		if (!buf || ft_strcmp(temp->data, buf) == 0)
			break ;
		write(fd[1], buf, ft_strlen(buf));
		write(fd[1], "\n", 1);
		free(buf);
	}
	close(fd[1]);
	if (cmd->heredoc[i] != -2)
		close(cmd->heredoc[i]);
	cmd->heredoc[i] = fd[0]; //todo(apancar): dup2(cmd->heredoc[i],fd[0])
	if (cmd->in == -1)
		return (print_err(temp->data, ERR_FILE_OPEN), FAILURE);
	return (SUCCESS);
}

int	handle_redr(t_token *token, t_cmd *cmd, t_state *state)
{
	t_token	*temp;

	if (!token)
		return (FAILURE);
	temp = token->next;
	if (!temp)
		return (FAILURE);
	if (access(temp->data, F_OK) == 0 && access(temp->data, W_OK) == -1)
	{
		state->status = 2;
		print_err(temp->data, ERR_FILE_PERMISSION_DENIED);
		return (FAILURE);
	}
	cmd->out = open(temp->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out == -1)
	{
		state->status = 1;
		print_err(temp->data, ERR_FILE_OPEN);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	handle_redrr(t_token *token, t_cmd *cmd, t_state *state)
{
	t_token	*temp;

	if (!token)
		return (FAILURE);
	temp = token->next;
	if (!temp)
		return (FAILURE);
	if (access(temp->data, F_OK) == 0 && access(temp->data, W_OK) == -1)
	{
		state->status = 2;
		print_err(temp->data, ERR_FILE_PERMISSION_DENIED);
		return (FAILURE);
	}
	cmd->out = open(temp->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out == -1)
	{
		state->status = 1;
		print_err(temp->data, ERR_FILE_OPEN);
		return (FAILURE);
	}
	return (SUCCESS);
}
