#include "minishell.h"

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
