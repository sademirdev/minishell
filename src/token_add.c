#include "minishell.h"
#include <stdlib.h>

t_token	*token_new(char *data, t_token_type type)
{
	t_token	*token;

	if (!data)
		return (NULL);
	token = (t_token *)malloc(sizeof(t_token));
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
	if (!root)
	{
		root = new;
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
// 		tmp = *token;
// 		printf("0. token->data:%s\ntoken:%p\n\n", (*token)->data, (*token));
// 		*token = new;
// 		printf("1. token->data%s\ntoken:%p\n\n", (*token)->data, (*token));
// 		new->next = tmp;
// 		new->prev = NULL;
// 		*token = new;
// 		printf("2.token->data:%s\ntoken:%p\n\n", (*token)->data, (*token));
// 		return ;

void	token_add_prev(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!token || !*token || !new)
		return ;
	if (!(*token)->prev)
	{
		tmp = *token;
		printf("0. token->data:%s\ntoken:%p\n\n", (*token)->data, (*token));
		*token = new;
		printf("1. token->data%s\ntoken:%p\n\n", (*token)->data, (*token));
		new->next = tmp;
		tmp->prev = new;
		new->prev = NULL;
		*token = (*token)->next;
		printf("2.token->data:%s\ntoken:%p\n\n", (*token)->data, (*token));
		return ;
	}
	tmp = (*token)->prev;
	(*token)->prev = new;
	new->next = *token;
	tmp->next = new;
	new->prev = tmp;
}
