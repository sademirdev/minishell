#include "../inc/minishell.h"
#include <stdlib.h>

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_alpha(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

bool	is_alnum_underscore(char c)
{
	return (is_digit(c) || is_alpha(c) || c == '_');
}

bool	is_valid_dollar(char *data, int64_t i)
{
	return (data[i] == '$' && (is_alpha(data[i + 1]) || data[i + 1] == '_'
			|| is_digit(data[i + 1]) || data[i + 1] == '?'));
}

char	*get_dollar_value(char *key)
{
	extern char	**environ;
	int64_t		i;
	int64_t		key_len;
	char		*value;

	// todo(sademir): use state.env instead
	i = 0;
	value = NULL;
	while (environ[i])
	{
		key_len = ft_strlen(key);
		if (ft_strncmp(environ[i], key, key_len) == 0
			&& environ[i][key_len] == '=')
		{
			value = ft_strdup(&environ[i][key_len + 1]);
			if (!value)
				(void)i; // todo(hkizrak-): handle
		}
		i++;
	}
	return (value);
}

char	*create_data_from_dollar(char *data, char *value, int64_t start,
		int64_t index)
{
	char	*new_data;
	int64_t	i;
	int64_t	j;
	int64_t	value_len;

	if (!data)
		return (NULL);
	value_len = ft_strlen(value);
	new_data = (char *)malloc((start + value_len + ft_strlen(data + index))
			* sizeof(char));
	if (!new_data)
		(void)index; // todo(apancar): handle
	i = 0;
	j = 0;
	while (i < start - 1)
		new_data[j++] = data[i++];
	i = 0;
	while (i < value_len)
		new_data[j++] = value[i++];
	while (data[index])
		new_data[j++] = data[index++];
	new_data[j] = '\0';
	return (new_data);
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
	free(value);
	return (start + value_len - 2);
}

void	extract_dollar_key_values(char **data, t_state *state, bool *has_dollar)
{
	int64_t	flag_single_quote;
	int64_t	i;
	int64_t	start;

	if (!data || !*data)
		return ;
	i = 0;
	flag_single_quote = 0;
	while ((*data)[i])
	{
		flag_single_quote = get_in_quote(flag_single_quote, (*data)[i]);
		if (flag_single_quote != '\'' && is_valid_dollar(*data, i))
		{
			*has_dollar = true;
			start = i + 1;
			if ((*data)[i + 1] == '0' || (*data)[i + 1] == '?')
				i = handle_special_dollar(data, start, i, state);
			else if ((*data)[i + 1] > '0' && (*data)[i + 1] <= '9')
				handle_number_dollar(data, start, ++i);
			else
				i = handle_regular_dollar(data, start, i + 1);
		}
		if ((*data)[i])
			i++;
	}
}

void	handle_dollar(t_token **root, t_state *state)
{
	t_token *temp;
	t_token *iter;
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