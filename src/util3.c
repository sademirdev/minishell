#include "minishell.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2, bool flag_free)
{
	char	*buf;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	buf = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		buf[j++] = s1[i++];
	i = 0;
	while (s2[i])
		buf[j++] = s2[i++];
	buf[j] = '\0';
	if (flag_free)
		free((void *)s1);
	return (buf);
}

int	ft_atoi(const char *str)
{
	size_t	i;
	int		sign;
	int		num;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	num = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) &s[i]);
		i++;
	}
	if ((char) c == '\0')
		return ((char *) &s[i]);
	return (NULL);
}

bool	is_al_underscore(char c)
{
	return (is_alpha(c) || c == '_');
}

char	**str_arr_append(char **str_arr, char *data)
{
	char	**new_str_arr;
	int		i;
	int		len;

	if (!str_arr || !data)
		return (NULL);
	i = 0;
	while (str_arr[i])
		i++;
	len = i;
	new_str_arr = (char **) malloc(sizeof(char *) * (len + 2));
	if (!new_str_arr)
		return (NULL);
	i = 0;
	while (str_arr[i])
	{
		new_str_arr[i] = str_arr[i];
		i++;
	}
	new_str_arr[i++] = data;
	new_str_arr[i] = NULL;
	free(str_arr);
	return (new_str_arr);
}
