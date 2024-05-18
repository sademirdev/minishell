#include "minishell.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

void	set_red_file_fds(t_token *token, t_cmd *cmd)
{
	bool		has_last_heredoc;
	t_token	*tmp;

	if (!token)
		return ;
	has_last_heredoc = false;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == RED_LL)
			has_last_heredoc = true;
		else if (tmp->type == RED_L)
			has_last_heredoc = false;
		tmp = tmp->next;
	}
	while (token)
	{
		if (token->type == RED_L)
			handle_redl(token, cmd, has_last_heredoc);
		else if (token->type == RED_R)
			handle_redr(token, cmd);
		else if (token->type == RED_RR)
			handle_redrr(token, cmd);
		token = token->next;
	}
}

void	set_heredoc_fds(t_token *token, t_cmd *cmd)
{
	(void)cmd;
	if (!token)
		return ;
	while (token)
	{
		if (token->type == RED_LL)
			handle_redll(token, cmd);
		token = token->next;
	}
}

void	handle_redl(t_token *token, t_cmd *cmd, bool has_last_heredoc)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token->next;
	if (temp && !temp->next && temp->prev && !temp->prev->prev)
		return ;
	if (access(temp->data, F_OK) == -1) // todo(apancar): check access()
	{
		print_err(temp->data, ERR_FILE_NOT_FOUND);
		return ;
	}
	if (access(temp->data, R_OK) == -1) // todo(apancar): check access()
	{
		print_err(temp->data, ERR_FILE_PERMISSION_DENIED);
		return ;
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
	{
		print_err(temp->data, ERR_FILE_OPEN);
		return ;
	}
}
#include <string.h>
void	handle_redll(t_token *token, t_cmd *cmd)
{
	t_token	*temp;
	char		*buf;
	int			fd[2];

	if (!token)
		return ;
	temp = token->next;

	if (!temp)
		return ;
	if (pipe(fd) == -1)
		return ;
	// printf("[info]\n");
	printf("token->data: |%s|\n", token->data);
	printf("temp->data: |%s|\n", temp->data);
	while (true)
	{
		buf = readline("> ");
		if (!buf || ft_strcmp(temp->data, buf) == 0)
		{
			printf("break\n");
			break ;
		}
		write(fd[1], buf, ft_strlen(buf));
		free(buf);
	}
	close(fd[1]);
	cmd->in = fd[0];
	if (cmd->in == -1)
	{
		print_err(temp->data, ERR_FILE_OPEN);
		return ;
	}
}

void	handle_redr(t_token *token, t_cmd *cmd)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token->next;
	if (!temp)
		return ;
	if (access(temp->data, F_OK) == 0 && access(temp->data, W_OK) == -1)
	{
		print_err(temp->data, ERR_FILE_PERMISSION_DENIED);
		return ;
	}
	cmd->out = open(temp->data, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->out == -1)
	{
		print_err(temp->data, ERR_FILE_OPEN);
		return ;
	}
}

void	handle_redrr(t_token *token, t_cmd *cmd)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token->next;
	if (!temp)
		return ;
	if (access(temp->data, F_OK) == 0 && access(temp->data, W_OK) == -1)
		// todo(apancar): check access()
	{
		print_err(temp->data, ERR_FILE_PERMISSION_DENIED);
		return ;
	}
	cmd->out = open(temp->data, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmd->out == -1)
	{
		print_err(temp->data, ERR_FILE_OPEN);
		return ;
	}
}
