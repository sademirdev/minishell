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
			return (i); // todo(fekiz): handle error
	}
	else
	{
		value = ft_strdup(state->argv[0]);
		if (!value)
			return (i - 1); // todo(fekiz): handle error
	}
	i++;
	new_data = create_data_from_dollar(*data, value, start, i);
	if (!new_data)
	{
		free(value);
		return (i); // todo(hkizrak-): handle
	}
	temp = *data;
	*data = new_data;
	free(temp);
	free(value);
	return (i - 1);
}

// static int check_key_existence(char *key, t_state *state)
// {
// 	int	i;

// 	i = 0;
// 	while (state->env[i])
// 	{
// 		if (ft_strncmp(state->env[i], key, ft_strlen(key)) == 0
// 			&& state->env[i][ft_strlen(key)] == '=')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

void	handle_number_dollar(char **data, int start, int i)
{
	char	*new_data;
	char	*temp;
	char	*empty_value;

	empty_value = ft_strdup("");
	if (!empty_value)
		return ; // todo(hkizrak-): handle
	i++;
	new_data = create_data_from_dollar(*data, empty_value, start, i);
	if (!new_data)
		return ; // todo(hkizrak-): handle
	temp = *data;
	*data = new_data;
	free(temp);
	free(empty_value);
}

int	handle_regular_dollar(char **data, int start, int i, t_state *state)
{
	char	*value;
	char	*new_data;
	char	*temp;
	char	*key;
	int		value_len;

	while (is_alnum_underscore((*data)[i]))
		i++;
	key = ft_substr(*data, start, i - start);
	if (!key)
		(void)i; // todo(hkizrak-): handle
	value = get_dollar_value(key, state);
	if (!value)
		(void)i; // todo(hkizrak-): handle
	new_data = create_data_from_dollar(*data, value, start, i);
	if (!new_data)
		(void)i; // todo(hkizrak-): handle
	temp = *data;
	*data = new_data;
	free(temp);
	free(key);
	value_len = ft_strlen(value);
	if (value_len == 0)
		return (free(value), start - 1);
	return (free(value), start + value_len - 1);
}
