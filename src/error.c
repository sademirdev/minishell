#include "minishell.h"
#include <unistd.h>
#include <errno.h>

// void	print_err(const char *file, int err_flag)
// {
// 	write(2, "minishell: ", 11);
// 	write(2, file, ft_strlen(file));
// 	if (err_flag == ERR_FILE_NOT_FOUND)
// 		write(2, ": No such file or directory\n", 28);
// 	else if (err_flag == ERR_FILE_PERMISSION_DENIED)
// 		write(2, ": Permission denied\n", 20);
// 	else if (err_flag == ERR_FILE_OPEN)
// 		write(2, ": No such file or directory\n", 28);
// 	else if (err_flag == ERR_FILE_NOT_VALID)
// 		write(2, ": not a valid identifier\n", 25);
// 	else if (err_flag == ERR_CMD_NOT_FOUND)
// 		write(2, ": command not found\n", 21);
// }

void	err_at(const char *cmd)
{
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, " \n", 2);
}

void	print_err(const char *cmd, int err)
{
	// err_at(ERR_STR_PREFIX);
	// err_at(cmd);
	(void)cmd;
	if (err == EACCES)
		err_at(strerror(EACCES));
	else if (err == ENOENT)
		err_at(strerror(ENOENT));
	else if (err == EISDIR)
		err_at(strerror(EISDIR));
	else if (err == ERR_CMD_NOT_FOUND)
		err_at(ERR_STR_CMD_NOT_FOUND);
	else
		err_at(ERR_STR_UNKNOWN);
}
