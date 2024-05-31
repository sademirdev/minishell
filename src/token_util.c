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

	if (!tmp || !*tmp || !root)
		return ;
	old_node = *tmp;
	if ((*tmp)->prev)
		(*tmp)->prev->next = (*tmp)->next;
	if ((*tmp)->next)
		(*tmp)->next->prev = (*tmp)->prev;
	// if (root == *tmp)
	// 	root = (*tmp)->next; // todo(apancar): check again unnecessary assignment
	*tmp = (*tmp)->next;
	token_dispose(&old_node);
}

int	token_arr_len(t_token **token_arr)
{
	int	i;

	if (!token_arr)
		return (0);
	i = 0;
	while (token_arr[i])
		i++;
	return (i);
}
