#include "minishell.h"
#include <stdlib.h>

int	token_append_meta_pipe(t_token **token)
{
	t_token	*new;
	char	*data;

	if (!token || !*token)
		return (FAILURE);
	data = ft_strdup("|");
	if (!data)
		return (FAILURE);
	new = token_new(data, PIPE);
	if (!new)
		return (free(data), FAILURE);
	token_add_prev(token, new);
	return (SUCCESS);
}

int	token_append_meta_redl(t_token **token)
{
	t_token	*new;
	char	*data;

	if (!token || !*token)
		return (FAILURE);
	data = ft_strdup("<");
	if (!data)
		return (FAILURE);
	new = token_new(data, RED_L);
	if (!new)
		return (free(data), FAILURE);
	token_add_prev(token, new);
	return (SUCCESS);
}

int	token_append_meta_redll(t_token **token)
{
	t_token	*new;
	char	*data;

	if (!token || !*token)
		return (FAILURE);
	data = ft_strdup("<<");
	if (!data)
		return (FAILURE);
	new = token_new(data, RED_LL);
	if (!new)
		return (free(data), FAILURE);
	token_add_prev(token, new);
	return (SUCCESS);
}

int	token_append_meta_redr(t_token **token)
{
	t_token	*new;
	char	*data;

	if (!token || !*token)
		return (FAILURE);
	data = ft_strdup(">");
	if (!data)
		return (FAILURE);
	new = token_new(data, RED_R);
	if (!new)
		return (free(data), FAILURE);
	token_add_prev(token, new);
	return (SUCCESS);
}

int	token_append_meta_redrr(t_token **token)
{
	t_token	*new;
	char	*data;

	if (!token || !*token)
		return (FAILURE);
	data = ft_strdup(">>");
	if (!data)
		return (FAILURE);
	new = token_new(data, RED_RR);
	if (!new)
		return (free(data), FAILURE);
	token_add_prev(token, new);
	return (SUCCESS);
}
