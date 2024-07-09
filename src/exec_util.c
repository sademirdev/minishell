#include "minishell.h"
#include <stdlib.h>

int	w_exit_status(int status)
{
	return ((status >> 8) & 0x000000ff);
}

bool	token_has_cmd(t_token *token)
{
	if (!token)
		return (false);
	while (token)
	{
		if (token->type == CMD)
			return (true);
		token = token->next;
	}
	return (false);
}

void	t_handle_cp_arg_init(t_handle_cp_arg *arg, int **fd, int arr_len)
{
	arg->fd = fd;
	arg->arr_len = arr_len;
}

int	cmd_init(t_cmd *cmd, int arr_len)
{
	int	i;

	cmd->argv = NULL;
	cmd->cmd = NULL;
	cmd->in = NAFD;
	cmd->out = NAFD;
	cmd->idx = 0;
	cmd->count = 0;
	cmd->heredoc = (int *) malloc(sizeof(int) * arr_len);
	if (!cmd->heredoc)
		return (FAILURE);
	i = 0;
	while (i < arr_len)
	{
		cmd->heredoc[i] = NAFD;
		i++;
	}
	return (SUCCESS);
}
