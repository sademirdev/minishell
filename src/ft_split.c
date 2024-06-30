#include "minishell.h"
#include <stdlib.h>

static int	ft_count_words(char const *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != (unsigned char) c
			&& (str[i + 1] == (unsigned char) c || !str[i + 1]))
		{
			count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_dispose_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
	return (NULL);
}

static char	**ft_fill_arr(char **arr, char const *str, char c)
{
	int	i;
	int	j;
	int	arr_i;

	i = 0;
	arr_i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		j = i;
		while (str[i] && str[i] != c)
			i++;
		if (i > j)
		{
			arr[arr_i] = ft_substr(str, j, i - j);
			if (arr[arr_i] == NULL)
				return (ft_dispose_arr(arr, arr_i));
			arr_i++;
		}
	}
	arr[arr_i] = NULL;
	return (arr);
}

char	**ft_split(char const *str, char c)
{
	char	**arr;

	if (!str)
		return (NULL);
	arr = (char **) malloc((ft_count_words(str, c) + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	return (ft_fill_arr(arr, str, c));
}
