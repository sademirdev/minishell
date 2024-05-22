#include "minishell.h"
#include <stdlib.h>

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
		if ((*data)[i] && (*data)[i] == '$' && (*data)[i + 1] && (*data)[i + 1] == '$')
			i++;
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
		if ((*data)[i] && flag_single_quote != '\'' && is_valid_dollar(*data, i))
			continue ;
		if ((*data)[i] && ((*data)[i] != '$' || flag_single_quote))
			i++;
		printf("at%c\n", (*data)[i]);
	}
}
