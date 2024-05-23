#include "minishell.h"
#include <stdlib.h>

void	handle_dollar(t_token **root, t_state *state)
{
	t_token	*temp;
	t_token	*iter;
	bool	has_dollar;

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

int64_t	handle_special_dollar(char **data, int64_t start, int64_t i,
		t_state *state)
{
	char	*new_data;
	char	*value;
	char	*tmp;

	i++;
	if ((*data)[i] == '?')
	{
		value = ft_itoa(state->status);
		if (!value)
			(void)value; // todo(fekiz): handle error
	}
	else
	{
		value = ft_strdup(state->argv[0]);
		if (!value)
			(void)value; // todo(fekiz): handle error
	}
	i++;
	new_data = create_data_from_dollar(*data, value, start, i);
	if (!new_data)
		(void)i; // todo(hkizrak-): handle
	tmp = *data;
	*data = new_data;
	free(tmp);
	return (i);
}

void	handle_number_dollar(char **data, int64_t start, int64_t i)
{
	char	*new_data;
	char	*tmp;
	char	*empty_value;

	empty_value = ft_strdup("");
	if (!empty_value)
		(void)i; // todo(hkizrak-): handle
	i++;
	new_data = create_data_from_dollar(*data, empty_value, start, i);
	if (!new_data)
		(void)i; // todo(hkizrak-): handle
	tmp = *data;
	*data = new_data;
	free(tmp);
}

int64_t	handle_regular_dollar(char **data, int64_t start, int64_t i)
{
	char	*value;
	char	*new_data;
	char	*tmp;
	char	*key;
	int64_t	value_len;

	while (is_alnum_underscore((*data)[i]))
		i++;
	key = ft_substr(*data, start, i - start);
	if (!key)
		(void)i; // todo(hkizrak-): handle
	value = get_dollar_value(key);
	if (!value)
		(void)i; // todo(hkizrak-): handle
	new_data = create_data_from_dollar(*data, value, start, i);
	if (!new_data)
		(void)i; // todo(hkizrak-): handle
	tmp = *data;
	*data = new_data;
	free(tmp);
	free(key);
	value_len = ft_strlen(value);
	if (value_len == 0)
		return (free(value), start - 1);
	return (free(value), start + value_len - 1);
}
