/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 15:40:48 by abostano          #+#    #+#             */
/*   Updated: 2024/04/25 14:12:05 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

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

//exec_c.c
void	lst_add(exec_c **head);
exec_c	**init_exec_s(t_token **head, exec_c **rtrn);
char	**add_args(char	**args, char *added);
void find_path_of_command(exec_c **head, char *envp[]);
//execute.c
int		ft_execute(t_token **head, char *envp[]);
//path_utils.c
size_t	ft_strlen(const char *a);
char	*ft_strnstr(const char *str1, const char *str2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strdup(const char *str);
//path.c
char	*ft_path(char *envp[]);
char	*ft_findpath(char *command, char *envp[]);
char	**ft_split(const char *s, char c);
char	*ft_strjoin(const char *str1, const char *str2);
//workit.c
void	workit(exec_c **head);
void	work_one_part(exec_c *head, int pipefd[]);

#endif