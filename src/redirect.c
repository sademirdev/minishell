#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int	set_red_file_fds(t_token *token, t_cmd *cmd, t_state *state)
{
	bool	has_last_heredoc;
	t_token	*tmp;
	int		exit_code;

	exit_code = 0;
	if (!token)
		return (1);
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
		{
			exit_code = handle_redl(token, cmd, has_last_heredoc, state);
			if (exit_code != 0)
				return (1);
		}
		else if (token->type == RED_R)
		{
			exit_code = handle_redr(token, cmd, state);
			if (exit_code != 0)
				return (1);
		}
		else if (token->type == RED_RR)
		{
			exit_code = handle_redrr(token, cmd, state);
			if (exit_code != 0)
				return (1);
		}
		token = token->next;
		if (!token)
			break ;
	}
	return (exit_code);
}

void	  set_heredoc_fds(t_token *token, t_cmd *cmd, int i)
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
