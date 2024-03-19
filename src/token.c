#include <stdlib.h>
#include "minishell.h"

t_token	*token_new(char *data, t_token_type type)
{
	t_token	*token;

	if (!data)
		return (NULL);
	token = (t_token *) malloc(sizeof (t_token));
	if (!token)
		return (NULL);
	token->next = NULL;
	token->prev = NULL;
	token->data = data;
	token->type = type;
	return (token);
}

void	token_add(t_token *root, t_token *new)
{
	if (!root)
		return ;
	while (root->next)
		root = root->next;
	root->next = new;
	root->next->prev = root;
}

void	token_add_next(t_token *token, t_token *new)
{
	if (!token || !new)
		return ;
	token->next = new;
	token->next->prev = token;
}

void	token_add_prev(t_token **token, t_token *new)
{
	if (!token || !*token || !new)
		return ;
	(*token)->prev = new;
	new->next = *token;
	// todo(hkizrak-): fix segmentation error!
}