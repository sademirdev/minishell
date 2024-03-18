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
}

void	token_dispose(t_token **root)
{
	t_token *temp;

	if (!root || !*root)
		return ;
	temp = *root;
	while (temp->next)
	{
		root = &temp;
		temp = temp->next;
		free((*root)->data);
		(*root)->data = NULL;
		free(*root);
		*root = NULL;
	}
}
