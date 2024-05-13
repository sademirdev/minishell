#include "minishell.h"
#include <unistd.h>

// < file 			: \n

// < file cmd 		: Success
// cmd < file		: Success

// < cmd file 		: bash: grep: No such file or directory
// file < cmd		: bash: a.txt: No such file or directory

// cmd file < 		: bash: syntax error near unexpected token `newline'
// cmd <			: bash: syntax error near unexpected token `newline'
// file <			: bash: syntax error near unexpected token `newline'

// < | 				: bash: syntax error near unexpected token `|'

void	handle_redl(t_token	*token)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token;
	if (temp->next->type == FILE && !temp->next->next)
	{
		if (access(temp->next, F_OK && X_OK))
			printf("\n");
		else
			printf("bash: %s: No such file or directory\n", temp->next->data);
	}
	else if (temp->next->type == CMD && !access(temp->next, F_OK && X_OK))
		printf("bash: %s: No such file or directory\n", temp->next->data);
	else if (ft_strncmp(temp->next, "\n", 1) == 0)
		printf("bash: syntax error near unexpected token `newline'\n");
	else if (temp->next->type == FILE && temp->next->next->type == CMD)
		//todo(apancar): handle execute
}