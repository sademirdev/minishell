/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:12:34 by abostano          #+#    #+#             */
/*   Updated: 2024/03/26 18:22:39 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"
#include <fcntl.h>

//Mainde başlatılacak fonksiyon burası olacak
int	ft_execute(t_token **head, char *envp[])
{
	pid_t	child_pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		error("pipe");
	child_pid = fork();
}

//Bu fonksiyon pipelar arasını bir promt olarak bölecek
t_execute	**init_promt(t_token **head, char *envp[])
{
	t_token		*tmp;
	t_execute	*exec;
	t_execute	**rtrn;

	exec = NULL;
	*rtrn = &exec;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type == PIPE)
		{
			pipe_came(exec);
			exec = exec->next;
		}
		else
			define_n_add(tmp, exec);
		tmp = tmp->next;
	}
	return (rtrn);
}

//Pipe geldiği durumda yeni bir execute yapısını oluşturacak
void	pipe_came(t_execute *tmp)
{
	t_execute	*added;

	added = malloc(sizeof(t_execute));
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = added;
}

//Tokenları execute yapısına ekleyecek
void	define_n_add(t_token *head, t_execute *exec)
{
	if (head->type == CMD)
		exec->cmd = ft_strdup(head->data);
	else if (head->type == ARG)
	{
		exec->args = ft_srtjoin(exec->args, head->data);
		exec->args = ft_srtjoin(exec->args, " ");
	}
	else if (head->type >= 4 && head->type <= 7)
		exec->operator = ft_strdup(head->data);
	else if (head->type == PIPE)
	{
		exec->next = malloc(sizeof(t_execute));
		exec = exec->next;
	}
}

//Genel manada bütün error mesajlarımızı burası döndürecek
void	error(char *str)
{
	perror(str);
	exit(1);
}