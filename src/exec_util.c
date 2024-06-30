#include "minishell.h"

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

void	t_handle_cp_arg_init(t_handle_cp_arg *arg, int (*fd)[2], int arr_len)
{
	arg->fd = fd;
	arg->arr_len = arr_len;
}
