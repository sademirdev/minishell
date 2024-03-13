#include <stdbool.h>
#include <stdint.h>

static int64_t	separated_list_len(char *prompt);

char	**separate_prompt_by_space(char *prompt)
{
	bool	flag;


	return 0;
}

static int64_t	separated_list_len(char *prompt)
{
	bool	flag;
	int64_t	count;
	int64_t	i;

	count = 0;
	flag = false;
	i = 0;
	while (prompt[i])
	{
		while (prompt[i] && prompt[i] == ' ')
			i++;
		while (prompt[i] && prompt[i] != '"' && prompt[i] != '\'')
		{
			if (prompt[i] == ' ' && prompt[i + 1] != ' ' && prompt[i + 1] != '\0')
				count++;
			i++;
		}
		if (!flag && prompt[i] == '"')
		{
			flag = true;
			count++;
			while (prompt[i] && prompt[i] != '"')
				i++;
			if (prompt[i] == '"')
				flag = false;
			if (!prompt[i])
				i++;
			if (flag)
				return (-42);
		}
		else if (!flag && prompt[i] == '\'')
		{
			flag = true;
			count++;
			while (prompt[i] && prompt[i] != '\'')
				i++;
			if (prompt[i] == '\'')
				flag = false;
			if (!prompt[i])
				i++;
			if (flag)
				return (-42);
		}
	}
	return (count);
}

#include <stdio.h>

int	main()
{
	printf("%lld\n" ,separated_list_len("at ''"));
}