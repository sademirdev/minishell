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

void	token_arr_dispose(t_token ***token_arr)
{
	int	i;

	if (!token_arr || !*token_arr || !**token_arr)
		return ;
	i = 0;
	while ((*token_arr)[i])
	{
		token_dispose_all(&(*token_arr)[i]);
		i++;
	}
	free(*token_arr);
	*token_arr = NULL;
}

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

bool	token_separation_meta_data_init(t_token_separation_meta_data *md, t_token *token)
{
	(*md).token_arr = (t_token **)malloc(sizeof(t_token *) * (token_count_pipe(token)
				+ 2));
	if (!(*md).token_arr)
		return (true);
	(*md).iter = token;
	(*md).tmp_root = token;
	(*md).i = 0;
	return (false);
}

t_token	**token_separate_by_pipe(t_token *token)
{
	t_token_separation_meta_data md;

	if (token_separation_meta_data_init(&md, token))
		return (NULL);
	while (md.iter)
	{
		if (md.iter->type == PIPE)
		{
			md.tmp = md.iter;
			md.token_arr[md.i] = md.tmp_root;
			md.tmp_root = md.iter->next;
			md.iter->prev->next = NULL; // note: segfault when prev NULL.
			md.iter = md.iter->next;
			if (md.tmp)
				token_dispose(&md.tmp);
			if (md.tmp_root && md.tmp_root->type == PIPE)
				return (NULL); // todo(sademir): give syntax error
			md.i++;
		}
		else
			md.iter = md.iter->next;
	}
	md.token_arr[md.i++] = md.tmp_root;
	md.token_arr[md.i] = NULL;
	return (md.token_arr);
}
