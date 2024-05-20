#include "../inc/execute.h"
#include <stdio.h>

void	add_element_token(t_token **head, char *content, int type);
//gcc -Wall -Wextra -Werror test/execute_test1.c src/exec/exec_c.c src/exec/execute.c src/exec/path_utils.c src/exec/path.c src/exec/workit.c
int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	t_token **head;

	head = (t_token **)malloc(sizeof(t_token *));
	*head = NULL;
	add_element_token(head, "ls", CMD);
	add_element_token(head, "-l", ARG);
	add_element_token(head, "|", PIPE);
	add_element_token(head, "grep", CMD);
	add_element_token(head, "0", ARG);
	ft_execute(head, envp);
}

// add element
void	add_element_token(t_token **head, char *content, int type)
{
	t_token *new;
	t_token *tmp;

	new = (t_token *)malloc(sizeof(t_token));
	new->data = content;
	new->type = type;
	new->next = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		tmp = new;
		return ;
	}
	else
	{
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = new;
		new->prev = tmp;
	
	}
}