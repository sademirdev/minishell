#include "minishell.h"

t_token	*token_get_root(t_token *node)
{
	if (!node)
		return (NULL);
	while (node && node->prev)
		node = node->prev;
	return (node);
}

t_token	*token_get_last(t_token *node)
{
	if (!node)
		return (NULL);
	while (node->next)
		node = node->next;
	return (node);
}

bool	token_is_just_meta(t_token **token)
{
	if (!token && !*token && !(*token)->data)
		return (false);
	if ((*token)->data[0] == '>' && (*token)->data[1] == '>'
		&& (*token)->data[2] == '\0')
		(*token)->type = RED_RR;
	else if ((*token)->data[0] == '<' && (*token)->data[1] == '<'
		&& (*token)->data[2] == '\0')
		(*token)->type = RED_LL;
	else if ((*token)->data[0] == '|' && (*token)->data[1] == '\0')
		(*token)->type = PIPE;
	else if ((*token)->data[0] == '<' && (*token)->data[1] == '\0')
		(*token)->type = RED_L;
	else if ((*token)->data[0] == '>' && (*token)->data[1] == '\0')
		(*token)->type = RED_R;
	else
		return (false);
	return (true);
}

void	token_old_del(t_token **tmp, t_token *root)
{
	t_token	*old_node;

	printf("tmp->prev->data:%s\ntmp:%p\nroot->data:%s\nroot:%p\n", (*tmp)->prev->data, (*tmp), root->data, root);
	if (!tmp || !*tmp || !root)
		return ;
	old_node = *tmp;
	if ((*tmp)->prev)
		(*tmp)->prev->next = (*tmp)->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = (*tmp)->prev;
	if (root == *tmp)
		root = (*tmp)->next;
	*tmp = (*tmp)->next;
	token_dispose(&old_node);
}
