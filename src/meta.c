#include "minishell.h"

t_token	*extract_meta_chars(t_token **root)
{
	t_token	*tmp;
	t_token	*last;

	tmp = *root;
	last = tmp;
	while (tmp)
	{
		if (!tmp->next)
			last = tmp;
		if (token_is_just_meta(&tmp))
			tmp = tmp->next;
		else if (token_append_meta(&tmp))
			token_old_del(&tmp, *root);
		else
			tmp = tmp->next;
	}
	return (token_get_root(last));
}

bool	is_meta(t_token_type type)
{
	return (type == PIPE || type == RED_L || type == RED_LL || type == RED_R
		|| type == RED_RR);
}

bool	is_meta_char(char *data, int64_t i)
{
	if (!data)
		return (false);
	if (data[i] == '>' && data[i + 1] == '>')
		return (true);
	if (data[i] == '<' && data[i + 1] == '<')
		return (true);
	return (data[i] == '|' || data[i] == '>' || data[i] == '<');
}

bool	has_meta_char(char *data, int64_t i)
{
	while (data[i])
	{
		if (is_meta_char(data, i))
			return (true);
		i++;
	}
	return (false);
}

t_token_type	get_meta_type(char *data, int64_t i)
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
