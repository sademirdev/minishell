#include "minishell.h"
#include <unistd.h>
#include <fcntl.h>

void	set_red_file_fds(t_token *token, t_cmd *cmd)
{
	(void)cmd;

	if (!token)
		return ;
	while (token)
	{
		if (token->type == RED_L)
			handle_redl(token, cmd);
		token = token->next;
	}
}

void	handle_redl(t_token	*token, t_cmd *cmd)
{
	t_token	*temp;

	if (!token)
		return ;
	temp = token->next;
	if (temp && !temp->next && temp->prev && !temp->prev->prev)
	{
		//printf("dont work\n");
		return ;
	}
	if (access(temp->data, F_OK) == -1) // todo(apancar): check access()
	{
		print_err(temp->data, ERR_FILE_NOT_FOUND);
		return ;
	}
	if (access(temp->data, R_OK) == -1) // todo(apancar): check access()
	{
		print_err(temp->data, ERR_FILE_PERMISSION_DENIED);
		return ;
	}
	cmd->in = open(temp->data, O_RDONLY);
	if (cmd->in == -1)
	{
		print_err(temp->data, ERR_FILE_OPEN);
		return ;
	}
}

// "< /bin/ls grep a"  : Binary file (standard input) matches


/*
Redirection of output causes the file whose name results from the expansion of word to be opened for writing on file descriptor n,
or the standard output (file descriptor 1) if n is not specified.
If the file does not exist it is created; if it does exist it is truncated to zero size.
The general format for redirecting output is:
[n]>[|]word
If the redirection operator is ‘>’, and the noclobber option to the set builtin has been enabled,
the redirection will fail if the file whose name results from the expansion of word exists and is a regular file.
If the redirection operator is ‘>|’, or the redirection operator is ‘>’
and the noclobber option is not enabled, the redirection is attempted even if the file named by word exists.
*/

// int64_t	has_redr(t_token *token)
// {
// 	return (1);
// }

// void	handle_redr(t_token *token)
// {
// 	t_token	*temp;

// 	if (!token)
// 		return ;
// 	if (!temp->next || ft_strcmp(temp->next->data, "\n") == 0)
// 		printf("bash: syntax error near unexpected token `newline'\n");
// 	if (temp->next->type == PIPE)
// 		printf("bash: syntax error near unexpected token `|'\n");

// }

