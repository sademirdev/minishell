#include "minishell.h"

void	assign_token_arr_types(t_token **token_arr)
{
	int	i;

	i = 0;
	if (!token_arr || !(*token_arr))
		return ;
	while (token_arr[i])
	{
		assign_token_types(token_arr[i]);
		i++;
	}
}

static void	assign_token_types_file(t_token *token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	while (temp)
	{
		if (temp->type == RED_L || temp->type == RED_R || temp->type == RED_RR)
		{
			temp = temp->next;
			if (temp)
				temp->type = RED_FILE;
			else
				break ;
		}
		else if (temp->type == RED_LL)
		{
			temp = temp->next;
			if (temp)
				temp->type = RED_HEREDOC;
			else
				break ;
		}
		temp = temp->next;
	}
}

void	assign_token_types(t_token *token)
{
	if (!token)
		return ;
	assign_token_types_file(token);
	while (token && token->type != NONE && token->type != ARG)
		token = token->next;
	if (token && token->type != RED_RR)
	{
		token->type = CMD;
		token = token->next;
	}
	while (token)
	{
		if (token->type == NONE)
			token->type = ARG;
		token = token->next;
	}
}
