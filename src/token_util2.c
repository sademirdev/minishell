#include "minishell.h"
#include <stdlib.h>

int token_count_pipe(t_token *token)
{
	int count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return count;
}

int token_arr_len(t_token **token_arr)
{
	int i = 0;
	if (!token_arr)
		return 0;
	while (token_arr[i])
		i++;
	return i;
}


int token_count_args(t_token *token)
{
	t_token *temp;
	int len = 0;
	bool on_arg = false;
	if (!token)
		return FAILURE;
	temp = token;
	while (temp)
	{
		if (temp->type == ARG)
		{
			len++;
			on_arg = true;
		}
		else if (on_arg)
			break;
		temp = temp->next;
	}
	return len;
}

int set_cmd_arg_and_path(t_token *token, t_state *state, t_cmd *cmd, int **pipe_fds)
{
	char **argv;
	char *cmd_path;
	
	if (!token || !cmd || !state)
		return FAILURE;
	if (token_is_built_in(token))
	{
		if (exec_built_in(state, token, cmd, pipe_fds) != SUCCESS)
		{
			token->data = NULL;
			return cmd_dispose(cmd), FAILURE;
		}
		token->data = NULL;
		return cmd_dispose(cmd), SUCCESS;
	}
	cmd_path = get_cmd_path(token, state);
	if (!cmd_path)
	{
		if (state->err != HANDLED && state->err != SUCCESS)
			return print_exec_err(state, token, 127, ERR_CMD_NOT_FOUND), FAILURE;
		return FAILURE;
	}
	cmd->cmd = cmd_path;
	argv = token_to_arg(token, cmd_path);
	if (!argv)
		return free(cmd_path), FAILURE;
	cmd->argv = argv;
	return SUCCESS;
}
