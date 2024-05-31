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
	t_token	*tmp;

	if (!token)
		return ;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == RED_L || tmp->type == RED_R || tmp->type == RED_RR)
		{
			tmp = tmp->next;
			if (tmp)
				tmp->type = RED_FILE;
			else
				break ;
		}
		else if (tmp->type == RED_LL)
		{
			tmp = tmp->next;
			if (tmp)
				tmp->type = RED_HEREDOC;
			else
				break ;
		}
		tmp = tmp->next;
	}
}

void	assign_token_types(t_token *token)
{
	if (!token)
		return ;
	assign_token_types_file(token);
	while (token && token->type != NONE && token->type != ARG)
		token = token->next;
	if (token)
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
