#include <stdlib.h>
#include "minishell.h"

int64_t	pass_quoted_str(char *p, int64_t *oi);

t_token	*separate_prompt_by_space(char *prompt)
{
	int64_t	i;
	int64_t	start;
	char	*data;
	t_token	*new;
	t_token	*tokens;

	if (!prompt)
		return (NULL);
	i = 0;
	start = 0;
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		start = i;
		while (prompt[i] && prompt[i] != ' ')
		{
			if (prompt[i] && (prompt[i] == '\'' || prompt[i] == '"'))
				if (pass_quoted_str(prompt, &i) == -42)
					return (NULL);
			while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\'' && prompt[i] != '"')
				i++;
		}
		data = ft_substr(prompt, start, i - start);
		if (!data)
			return (token_dispose(tokens), NULL);
		new = token_new(data, NONE);
		if (!new)
			return (free(data), token_dispose(tokens), NULL);
		tokens = token_add_last(tokens, new);
		if (!tokens)
			return (free(data), free(new), NULL);
	}
	return (tokens);
}

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

t_token	*extract_meta_chars(t_token	*tokens)
{
	// t_token	tmp;

	// while (tokens->next)
	// {
	// 	// todo(sademir): complete this function!
	// 	tokens = tokens->next;
	// }
	(void)tokens;
	return (NULL);
}
