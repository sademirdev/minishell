#include "minishell.h"
#include <stdlib.h>

int64_t	pass_quoted_str(char *p, int64_t *oi)
{
	int64_t	i;

	i = *oi;
	if (p[i] == '"')
	{
		i++;
		while (p[i] && p[i] != '"')
			i++;
		*oi = i;
		if (!p[i])
			return (-42);
		(*oi)++;
	}
	else if (p[i] == '\'')
	{
		i++;
		while (p[i] && p[i] != '\'')
			i++;
		*oi = i;
		if (!p[i])
			return (-42);
		(*oi)++;
	}
	return (0);
}

char	get_in_quote(char old, char data)
{
	if (old == '"' && data == '"')
		old = 0;
	else if (old == '\'' && data == '\'')
		old = 0;
	else if (data == '\'' || data == '"')
		old = data;
	return (old);
}

bool	is_unnecessary_quote(int64_t *quote, char data)
{
	if (*quote)
	{
		if (data == *quote)
		{
			*quote = 0;
			return (true);
		}
	}
	else
	{
		if (data == '"')
		{
			*quote = '"';
			return (true);
		}
		else if (data == '\'')
		{
			*quote = '\'';
			return (true);
		}
	}
	return (false);
}

int64_t	count_unnecessary_quotes(char *data)
{
	int64_t	quote;
	int64_t	i;
	int64_t	counter;

	i = 0;
	counter = 0;
	quote = 0;
	while (data[i])
	{
		if (data[i] && is_unnecessary_quote(&quote, data[i]))
			counter++;
		i++;
	}
	return (counter);
}

bool	has_unnecessary_quotes(char *data)
{
	int64_t	quote;
	int64_t	i;

	i = 0;
	while (data[i])
	{
		is_unnecessary_quote(&quote, data[i]);
		if (data[i] && is_unnecessary_quote(&quote, data[i]))
			return (true);
		i++;
	}
	return (false);
}

void	delete_unnecessary_quotes(char **data)
{
	int64_t i;
	int64_t j;
	int64_t quote;
	char		*new_data;

	new_data = (char *) malloc(sizeof(char) * (ft_strlen(*data) - count_unnecessary_quotes(*data) + 1));
	if (!new_data)
		return ; // todo(sademir): handle error
	i = 0;
	j = 0;
	quote = 0;
	while ((*data)[i])
	{
		if ((*data)[i] && !is_unnecessary_quote(&quote, (*data)[i]))
			new_data[j++] = (*data)[i];
		i++;
	}
	new_data[j] = '\0';
	free(*data);
	*data = new_data;
}

void	handle_unnecessary_quotes(t_token *root)
{
	t_token	*tmp;

	if (!root)
		return ;
	tmp = root;
	while (tmp)
	{
		if (has_unnecessary_quotes(tmp->data))
			delete_unnecessary_quotes(&tmp->data);
		tmp = tmp->next;
	}
}
