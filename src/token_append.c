#include "minishell.h"

// todo(hkizrak-): check possible errors for side by side metas (throw syntax
// error)  a<b
bool	token_append_meta(t_token **token)
{
	t_token_append_meta_data	md;

	token_append_meta_data_init(&md, token);
	while ((*token)->data[md.i])
	{
		md.in_quote = get_in_quote(md.in_quote, (*token)->data[md.i]);
		md.type = get_meta_type((*token)->data, md.i);
		if (is_meta(md.type) && !md.in_quote)
		{
			md.has_meta = true;
			token_append_all(token, md.start, md.i, md.type);
			if (md.type == RED_LL || md.type == RED_RR)
				md.i++;
			if ((*token)->data[md.i + 1] && !is_meta_char((*token)->data, md.i
					+ 1))
				md.start = md.i + 1;
			else
				md.start = -1;
		}
		if (!(*token)->data[md.i + 1] && md.has_meta && md.start != -1)
			token_append_str(token, md.start, md.i + 1);
		md.i++;
	}
	return (md.has_meta);
}

void	token_append_all(t_token **token, int64_t start, int64_t i,
		t_token_type type)
{
	if (start != -1)
		token_append_str(token, start, i);
	// todo(hkizrak-): check if there are two PIPE side by side after this func
	// (throw syntax error)
	if (type == PIPE)
		token_append_meta_pipe(token);
	if (type == RED_L)
		token_append_meta_redl(token);
	// todo(hkizrak-): check if there are > or >> after this created node (throw
	// syntax error)
	if (type == RED_LL)
		token_append_meta_redll(token);
	if (type == RED_R)
		token_append_meta_redr(token);
	// todo(hkizrak-): check if there are < or << after this created node (throw
	// syntax error)
	if (type == RED_RR)
		token_append_meta_redrr(token);
}

void	token_append_meta_data_init(t_token_append_meta_data *md,
		t_token **token)
{
	md->i = 0;
	if (!is_meta_char((*token)->data, md->i))
		md->start = 0;
	else
		md->start = -1;
	md->has_meta = false;
	md->in_quote = 0;
}

void	token_append_str(t_token **token, int64_t start, int64_t i)
{
	t_token	*new;
	char	*data;

	data = ft_substr((*token)->data, start, i - start);
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, NONE);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}