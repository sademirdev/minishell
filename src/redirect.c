#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	set_red_file_fds(t_token *token, t_cmd *cmd)
{
	bool	has_last_heredoc;
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

void	  set_heredoc_fds(t_token *token, t_cmd *cmd, int64_t i)
{
	if (!token)
		return ;
	while (token)
	{
		if (token->type == RED_LL)
			handle_redll(token, cmd, i);
		token = token->next;
	}
}
