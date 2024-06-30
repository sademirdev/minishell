#include "minishell.h"
#include <stdlib.h>

int	pass_quoted_str(char *p, int *oi)
{
	int	i;

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

bool	is_unnecessary_quote(int *quote, char data)
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

int	count_unnecessary_quotes(char *data)
{
	int	quote;
	int	i;
	int	counter;

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
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (data[i])
	{
		is_unnecessary_quote(&quote, data[i]);
		if (data[i] && is_unnecessary_quote(&quote, data[i]))
			return (true);
		i++;
	}
	return (false);
}
