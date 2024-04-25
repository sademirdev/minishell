/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:18:47 by abostano          #+#    #+#             */
/*   Updated: 2024/04/25 13:45:47 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"
#include <unistd.h>

char	*ft_path(char *envp[])
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
	return (path);
}

char	*ft_findpath(char *command, char *envp[])
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	paths = ft_split(ft_path(envp), ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, command);
		if (access(path, X_OK) == 0)
			return (path);
		free(tmp);
		i++;
	}
	return (NULL);
}

static size_t	ft_toklen(const char *s, char c)
{
	size_t	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**ft_split(const char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	len;

	if (!s)
		return (0);
	i = 0;
	ret = malloc(sizeof(char *) * (ft_toklen(s, c) + 1));
	if (!ret)
		return (0);
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c && ++len)
				++s;
			ret[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strjoin(const char *str1, const char *str2)
{
	char	*r;
	int		a;
	int		b;

	a = 0;
	b = 0;
	if (!str1 || !str2)
		return (0);
	r = (char *)malloc((ft_strlen(str1) + ft_strlen(str2)) * sizeof(char) + 1);
	if (!r)
		return (0);
	while (str1[a])
	{
		r[a] = str1[a];
		a++;
	}
	while (str2[b])
	{
		r[a] = str2[b];
		a++;
		b++;
	}
	r[a] = '\0';
	return (r);
}