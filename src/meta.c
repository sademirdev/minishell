#include "minishell.h"
#include <stdlib.h>

t_token	*extract_meta_chars(t_token **root)
{
	t_token	*temp;
	t_token	*last;
	t_token	*temp_prev;

	temp = *root;
	last = temp;
	temp_prev = NULL;
	while (temp)
	{
		if (!temp->next)
			last = temp;
		if (token_is_just_meta(&temp))
			temp = temp->next;
		else if (token_append_meta(&temp))
		{
			if ((*temp).prev)
				temp_prev = (*temp).prev;
			token_old_del(&temp, *root);
		}
		else
			temp = temp->next;
	}
	if (temp_prev)
		return (token_get_root(temp_prev));
	return (token_get_root(last));
}

bool	is_meta(t_token_type type)
{
	return (type == PIPE || type == RED_L || type == RED_LL || type == RED_R
		|| type == RED_RR);
}

bool	is_meta_char(char *data, int i)
{
	if (!data)
		return (false);
	if (data[i] == '>' && data[i + 1] == '>')
		return (true);
	if (data[i] == '<' && data[i + 1] == '<')
		return (true);
	return (data[i] == '|' || data[i] == '>' || data[i] == '<');
}

t_token_type	get_meta_type(char *data, int i)
{
	if (data[i] == '|')
		return (PIPE);
	if (data[i] == '<' && data[i + 1] == '<')
		return (RED_LL);
	if (data[i] == '<')
		return (RED_L);
	if (data[i] == '>' && data[i + 1] == '>')
		return (RED_RR);
	if (data[i] == '>')
		return (RED_R);
	else
		return (NONE);
}
