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
	t_execute	**promts;

	promts = (t_execute **)malloc(sizeof(t_execute *));
	exec = *promts;
	tmp = *head;
	while (tmp)
	{
		if (tmp->type != PIPE)
		{
			define_n_add(tmp, exec, envp);
		}
		else
			exec = exec->next;
		tmp = tmp->next;
	}
	
	return (0);
}

//Bu fonksiyon tokenin tipine göre işlem yapacak
t_execute	*define_n_add(t_token *head, t_execute *exec, char *envp[])
{
	if (head->type <= 7 && head->type >= 4)
		exec->operator = head->data;
	else if (head->type == CMD)
	{
		exec->cmd = head->data;
		exec->path_of_cmd = ft_findpath(exec->cmd, envp);
	}

}

//Genel manada bütün error mesajlarımızı burası döndürecek
void	error(char *str)
{
	perror(str);
	exit(1);
}