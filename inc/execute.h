/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:40:48 by abostano          #+#    #+#             */
/*   Updated: 2024/03/26 18:40:02 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

typedef struct s_execute
{
	char	*cmd;
	char	*operator;
	char	*file;
	char	*path_of_cmd;
	char	*args;
	struct s_execute	*next;
}	t_execute;

size_t	ft_strlen(const char *a);
char	*ft_strnstr(const char *str1, const char *str2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *str);

#endif