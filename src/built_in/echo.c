#include "../../inc/built_in.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

int64_t	ft_strlen(const char *s)
{
	int64_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
int64_t	ft_strlcpy(char *dst, const char *src, int64_t dst_size)
{
	int64_t	i;

	if (dst_size == 0)
		return (ft_strlen(src));
	i = 0;
	while (src[i] && i < dst_size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

int64_t	ft_strcmp(const char *s1, const char *s2)
{
	int64_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] != s2[i])
		return (s1[i] - s2[i]);
	return (0);
}
char *ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int64_t	i;
	int64_t	j;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}
char *ft_strdup(const char *s)
{
	char	*result;
	int64_t	i;

	if (!s)
		return (NULL);
	result = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = s[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int64_t	handle_echo(t_built_in *built)
{
	t_built_in	*temp;
	char		*buffer;
	bool		new_line;

	buffer = ft_strdup("");
	if (!built || !buffer)
		return (free(buffer), 1);
	temp = built->next;
	new_line = ft_strcmp(temp->data, "-n") == 0;
	if (new_line)
		temp = temp->next;
	while (temp && temp->type == ARG)
	{
		buffer = ft_strjoin(buffer, temp->data);
		if (!buffer)
			return (free(buffer), 1);
		if (temp->next && temp->next->type == ARG)
		{
			buffer = ft_strjoin(buffer, " ");
			if (!buffer)
				return (free(buffer), 1);
		}
		temp = temp->next;
	}
	printf("%s", buffer);
	if (!new_line)
		printf("\n");
	return (0);
}

int	main()
{
	t_built_in	*temp;

	temp = (t_built_in *)malloc(sizeof(t_built_in));
	temp->data = "echo";
	temp->type = CMD;

	// temp->next = NULL;
	temp->next = (t_built_in *)malloc(sizeof(t_built_in));
	temp->next->data = "aaa";
	temp->next->type = ARG;
	temp->next->next = (t_built_in *)malloc(sizeof(t_built_in));
	temp->next->next->data = "|";
	temp->next->next->type = PIPE;
	temp->next->next->next = NULL;
	temp->next->next->next = (t_built_in *)malloc(sizeof(t_built_in));
	temp->next->next->next->data = "fdgfdgfdd";
	temp->next->next->next->type = ARG;
	temp->next->next->next->next = NULL;
	handle_echo(temp);
	return (0);
}

/*
echo -n Hello, World!
before-after meta
*/
