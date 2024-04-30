#include "minishell.h"

void	assign_token_arr_types(t_token **token_arr)
{
	int64_t	i;

	i = 0;
	if (!token_arr || !(*token_arr))
		return ;
	while (token_arr[i])
	{
		assign_token_types(token_arr[i]);
		i++;
	}
}

void	assign_token_types(t_token *token)
{
	if (!token)
		return ;
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
