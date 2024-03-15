#include <stdbool.h>
#include <stdint.h>

int64_t	separated_list_len(char *prompt);
int64_t	pass_quoted_str(char *p, int64_t *oi);

// char	**separate_prompt_by_space(char *prompt)
// {
// 	return 0;
// }

int64_t	separated_list_len(char *prompt)
{
	int64_t	i;
	int64_t	len;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		if (prompt[i])
			len++;
		while (prompt[i] && prompt[i] != ' ')
		{
			if (prompt[i] && (prompt[i] == '\'' || prompt[i] == '"'))
				if (pass_quoted_str(prompt, &i) == -42)
					return (-42);
			while (prompt[i] && prompt[i] != ' ' && prompt[i] != '\'' && prompt[i] != '"')
				i++;
		}
	}
	return (len);
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
