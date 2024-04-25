#include "minishell.h"

void	token_append_meta_pipe(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup("|");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, PIPE);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redl(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup("<");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_L);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redll(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup("<<");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_LL);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redr(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup(">");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_R);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}

void	token_append_meta_redrr(t_token **token)
{
	t_token	*new;
	char	*data;

	data = ft_strdup(">>");
	if (!data)
		return ; // todo(sademir): handle error
	new = token_new(data, RED_RR);
	if (!new)
		return ; // todo(sademir): handle error
	token_add_prev(token, new);
}
