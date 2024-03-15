#include <stdbool.h>
#include <stdint.h>

static int64_t	separated_list_len(char *prompt);
static int64_t	recursive(char *prompt, int64_t *i, int64_t *flag);

char	**separate_prompt_by_space(char *prompt)
{
	return 0;
}

static int64_t	separated_list_len(char *prompt)
{
	int64_t	flag;
	int64_t	count;
	int64_t	i;

	count = 0;
	flag = 0;
	i = 0;
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		while (prompt[i] && prompt[i] != '"' && prompt[i] != '\'')
		{
			while (prompt[i] == ' ')
				i++;
			if (!prompt[i])
				break ;
			count++;
			while (prompt[i] && prompt[i] != ' ')
			{
				if (prompt[i] == '\'')
				{
					flag = prompt[i];
					i++;
					if (recursive(prompt, &i, &flag) == -42)
						return (-42);
				}
				i++;
			}
		}
		if (!flag && prompt[i] == '\'')
		{
			flag = prompt[i];
			count++;
			i++;
			if (recursive(prompt, &i, &flag) == -42)
				return (-42);
			if (prompt[i])
				i++;
		}
	}
	return (count);
}

int64_t	recursive(char *prompt, int64_t *i, int64_t *flag)
{
	while (prompt[*i] && prompt[*i] != '\'')
		(*i)++;
	if (prompt[*i] == '\'')
	{
		*flag = 0;
		if (prompt[*i] && prompt[*i + 1] != ' ' && prompt[*i + 1] != '\'')
			while (prompt[*i] != ' ' && prompt[*i])
				(*i)++;
		if (prompt[*i] && prompt[*i + 1] == '\'')
		{
			(*i)++;
			*flag = prompt[*i];
			(*i)++;
			return (recursive(prompt, i, flag));
		}
	}
	else
		return (-42);
	return (0);
}

// int64_t	len(char *p)
// {
// 	int64_t	i;
// 	int64_t	c;
// 	int64_t	f;

// 	i = ;
// }

#include <stdio.h>

int	main()
{
	// printf("%lld\n" ,separated_list_len("'aa''a a'"));
	printf("%lld\n" , separated_list_len("'aa''a a'a ' a' 'a'"));
	// printf("%lld\n" ,separated_list_len("at at    a''  ''at"));
}