#include "minishell.h"
#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] != s2[i] || i == n - 1)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *src)
{
	char	*str;
	int		len;
	int		i;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (src[i])
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, int start, int len)
{
	char	*buf;
	int		i;
	int		slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	buf = (char *) malloc ((len + 1) * sizeof(char));
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

int	ft_strlcpy(char *dst, const char *src, int dst_size)
{
	int	i;

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

static int	ft_count_digit(int n)
{
	int	c;

	if (n == 0)
		return (1);
	c = 0;
	while (n)
	{
		c++;
		n /= 10;
	}
	return (c);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

static void	ft_strrev(char *str)
{
	int		length;
	int		i;
	char	temp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		temp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = temp;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	int		length;

	is_neg = (n < 0);
	str = (char *)malloc((ft_count_digit(n) + is_neg + 1) * sizeof(char));
	if (!str)
		return (NULL);
	length = 0;
	if (n == 0)
	{
		str[0] = '0';
		length++;
	}
	while (n != 0)
	{
		str[length++] = '0' + ft_abs(n % 10);
		n /= 10;
	}
	if (is_neg)
		str[length++] = '-';
	str[length] = '\0';
	ft_strrev(str);
	return (str);
}

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
