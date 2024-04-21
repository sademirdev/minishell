#include "minishell.h"
#include <stdlib.h>

void	token_dispose(t_token **token)
{
	if (!token)
		return ;
	if (*token)
	{
		free((*token)->data);
		(*token)->data = NULL;
	}
	free(*token);
	*token = NULL;
}

void	token_dispose_all(t_token **token)
{
	if (!token || !*token)
		return ;
	if ((*token)->next)
		token_dispose_all(&(*token)->next);
	token_dispose(token);
}

int64_t	token_count_pipe(t_token *token)
{
	int64_t	count;

	count = 0;
	while (token)
	{
		if (token->type == PIPE)
			count++;
		token = token->next;
	}
	return (count);
}

// todo(apancar): separate function for norm
t_token	**token_separate_by_pipe(t_token *token)
{
	t_token	**token_arr;
	t_token	*iter;
	t_token	*tmp;
	t_token	*tmp_root;
	int64_t	i;

	token_arr = (t_token **)malloc(sizeof(t_token *) * (token_count_pipe(token)
				+ 2));
	printf("len: %lld\n", token_count_pipe(token));
	if (!token_arr)
		return (NULL);
	iter = token;
	tmp_root = token;
	i = 0;
	while (iter)
	{
		if (iter->type == PIPE)
		{
			tmp = iter;
			token_arr[i] = tmp_root;
			tmp_root = iter->next;
			iter->prev->next = NULL;
			iter = iter->next;
			if (tmp)
				token_dispose(&tmp);
			if (tmp_root && tmp_root->type == PIPE)
				return (NULL); // todo(sademir): give syntax error
			i++;
		}
		else
			iter = iter->next;
	}
	token_arr[i++] = tmp_root;
	token_arr[i] = NULL;
	return (token_arr);
}
