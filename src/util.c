#include <stdlib.h>
#include "minishell.h"

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

char	*ft_strdup(const char *src)
{
	char	*str;
	int64_t	len;
	int64_t	i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	str = (char *) malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, int64_t len)
{
	char	*buf;
	int64_t	i;
	int64_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	buf = (char *) malloc((len + 1) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		buf[i] = s[start + i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
