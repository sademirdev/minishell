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
		return (print_err("##handle_redl.if1##", state, 0), FAILURE);
	if (access(temp->data, R_OK) == -1)
		return (print_err("##handle_redl.if2##", state, 2), FAILURE);
	if (has_last_heredoc)
		close(open(temp->data, O_RDONLY));
	else
	{
		if (cmd->in != -2)
			close(cmd->in);
		cmd->in = open(temp->data, O_RDONLY);
	}
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
	cmd->heredoc[i] = fd[0];
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
		return (print_err("##handle_redr.if1##", state, 2), FAILURE);
	cmd->out = open(temp->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out == -1)
		return (print_err("##handle_redr.if2##", state, 1), FAILURE);
	return (SUCCESS);
}

int	handle_redrr(t_token *token, t_cmd *cmd, t_state *state)
{
	t_token	*temp;

	if (!token)
		return (FAILURE);
	temp = token->next;
	if (access(temp->data, F_OK) == 0 && access(temp->data, W_OK) == -1)
		return (print_err("##handle_redrr.if1##", state, 2), FAILURE);
	cmd->out = open(temp->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out == -1)
		return (print_err("##handle_redrr.if2##", state, 1), FAILURE);
	return (SUCCESS);
}
