#include "minishell.h"
#include <stdlib.h>

void	handle_dollar(t_token **root, t_state *state)
{
	t_token		*temp;
	t_token		*iter;
	bool		has_dollar;

	if (!root || !*root || !state)
		return ;
	iter = *root;
	while (iter)
	{
		has_dollar = false;
		temp = iter;
		iter = iter->next;
		extract_dollar_key_values(&temp->data, state, &has_dollar);
		if (has_dollar)
		{
			if (!temp->prev)
				token_insert_dollar_nodes(root);
			else
				token_insert_dollar_nodes(&temp);
		}
	}
}

int	handle_special_dollar(char **data, int start, int i,
		t_state *state)
{
	char	*new_data;
	char	*value;
	char	*temp;

	i++;
	if ((*data)[i] == '?')
	{
		value = ft_itoa(state->status);
		if (value < 0)
			return (i);
	}
	else
	{
		value = ft_strdup(state->argv[0]);
		if (!value)
			return (i - 1);
	}
	i++;
	new_data = create_data_from_dollar(*data, value, start, i);
	if (!new_data)
		return (free(value), i);
	temp = *data;
	*data = new_data;
	return (free(temp), free(value), i - 1);
}

void	handle_number_dollar(char **data, int start, int i)
{
	char	*new_data;
	char	*temp;
	char	*empty_value;

	empty_value = ft_strdup("");
	if (!empty_value)
		return ;
	i++;
	new_data = create_data_from_dollar(*data, empty_value, start, i);
	if (!new_data)
		return ;
	temp = *data;
	*data = new_data;
	free(temp);
	free(empty_value);
}

static char	*str_get_empty_when_null(char *value)
{
	if (!value)
		return (ft_strdup(""));
	return (value);
}

int	handle_regular_dollar(char **data, int start, int i, t_state *state)
{
	char	*value;
	char	*new_data;
	char	*temp;
	char	*key;
	int		len;

	while (is_alnum_underscore((*data)[i]))
		i++;
	key = ft_substr(*data, start, i - start);
	if (!key)
		return (start - 1);
	value = get_dollar_value(key, state);
	value = str_get_empty_when_null(value);
	if (!value)
		return (1);
	new_data = create_data_from_dollar(*data, value, start, i);
	if (!new_data)
		return (start - 1);
	temp = *data;
	*data = new_data;
	len = ft_strlen(value);
	if (len == 0)
		return (free(key), free(temp), free(value), start - 1);
	return (free(key), free(temp), free(value), start + len - 1);
}
