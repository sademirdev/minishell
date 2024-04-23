/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:40:48 by abostano          #+#    #+#             */
/*   Updated: 2024/04/04 10:00:06 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

typedef struct execute
{
	char	*cmd;
	char	*file;
	char	*operator;
	char	**args;
	char	*path;
	char	**full_command;
	struct execute *next;
}	exec_c;

size_t	ft_strlen(const char *a);
char	*ft_strnstr(const char *str1, const char *str2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *str);

#endif