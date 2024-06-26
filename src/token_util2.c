#include "minishell.h"

int	token_count_pipe(t_token *token)
{
	int	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

int	token_arr_len(t_token **token_arr)
{
	int	i;

	if (!token_arr)
		return (0);
	i = 0;
	while (token_arr[i])
		i++;
	return (i);
}

int	token_count_args(t_token *token)
{
	t_token	*temp;
	int		len;
	bool	on_arg;

	if (!token)
		return (FAILURE);
	temp = token;
	len = 0;
	on_arg = false;
	while (temp)
	{
		if (temp->type == ARG)
		{
			len++;
			on_arg = true;
		}
		else if (on_arg)
			break ;
		temp = temp->next;
	}
	return (len);
}

int	set_cmd_arg_and_path(t_token *token, t_state *state, t_cmd *cmd)
{
	char	**argv;
	char	*cmd_path;

	if (!token || !cmd || !state)
		return (FAILURE);
	cmd_path = get_cmd_path(token, state);
	if (!cmd_path)
		return (FAILURE);
	argv = token_to_arg(token, cmd_path);
	if (!argv)
		return (FAILURE);
	cmd->cmd = cmd_path;
	cmd->argv = argv;
	return (SUCCESS);
}
