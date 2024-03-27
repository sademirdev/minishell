#include <stdlib.h>
#include "minishell.h"

t_token	*token_new(char *data, t_token_type type)
{
	t_token	*token;

	if (!data)
		return (NULL);
	token = (t_token *) malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->prev = NULL;
	token->data = data;
	token->type = type;
	return (token);
}

t_token	*token_add_last(t_token *token, t_token *new)
{
	t_token	*root;

	root = token;
	printf("token: %p\n", token);
	if (!root)
	{
		root = (t_token *) malloc(sizeof(t_token));
		if (!root)
			return (NULL);
		return (root);
	}
	while (token->next)
		token = token->next;
	token->next = new;
	if (token->next)
		token->next->prev = token;
	return (root);
}

void	token_add_next(t_token *token, t_token *new)
{
	t_token	*tmp;

	if (!token || !new)
		return ;
	tmp = token->next;
	token->next = new;
	new->prev = token;
	new->next = tmp;
	tmp->prev = new;
}

void	token_add_prev(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!token || !*token || !new)
		return ;
	if (!(*token)->prev)
	{
		tmp = *token;
		*token = new;
		new->next = tmp;
		tmp->prev = new;
		new->prev = NULL;
		return ;
	}
	tmp = (*token)->prev;
	(*token)->prev = new;
	new->next = *token;
	tmp->next = new;
	new->prev = tmp;
}

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

	token_arr = (t_token **) malloc(sizeof(t_token *) * (token_count_pipe(token) + 1));
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
	token_arr[i] = NULL;
	return (token_arr);
}
