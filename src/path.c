/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:18:47 by abostano          #+#    #+#             */
/*   Updated: 2024/03/26 16:11:21 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"
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
