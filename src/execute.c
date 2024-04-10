/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:12:34 by abostano          #+#    #+#             */
/*   Updated: 2024/04/04 11:16:16 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"
#include <fcntl.h>

//Mainde başlatılacak fonksiyon burası olacak
int	ft_execute(t_token **head, char *envp[])
{
	t_token	*tmp;

	tmp = *head;
	while (tmp)
	{

		tmp = tmp->next;
	}
}

void	ft_recursive(t_token **head, char *envp[])
{
	pid_t	pid;

}

void	ft_execute_cmd(t_token **head, char *envp[], int pipefd[])
{
	t_token	*tmp;


}

void	lst_add(exec_c **head)
{
	exec_c	*tmp;
	exec_c	*added;

	tmp = *head;
	added = (exec_c *)malloc(sizeof(exec_c));
	if (tmp == NULL)
	{
        *head = added;
    }
	else
	{
        while (tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = added;
    }
	added->cmd = NULL;
	added->file = NULL;
	added->operator = NULL;
	added->args = NULL;
	added->next = NULL;
}

exec_c	**init_exec_s(t_token **head)
{
	exec_c	**rtrn;
	exec_c	*test;
	t_token	*tmp;

	rtrn = (exec_c **)malloc(sizeof(exec_c *));
	*rtrn = NULL;
	test = *rtrn;
	tmp = *head;
	while (tmp)
	{
		if (tmp->prev == NULL || tmp->type == PIPE)
		{
			lst_add(rtrn);
			if (tmp->prev != NULL)
				test = test->next;
		}
		if (tmp->type == CMD)
			test->cmd = tmp->data;
		else if (tmp->type == ARG)
			test->args = add_args(test->args, tmp->data);
		else if (tmp->type >= 4 && tmp->type <= 7)
			test->operator = tmp->data;
		tmp = tmp->next;
	}
	
}

char	**add_args(char	**args, char *added)
{
	char	**new_args;
	int		i;

	i = 0;
	while (args[i])
		i++;
	new_args = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (args[i])
	{
		new_args[i] = ft_strdup(args[i]);
		i++;
	}
	new_args[i++] = ft_strdup(added);
	new_args[i + 1] = NULL;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	return (new_args);

}