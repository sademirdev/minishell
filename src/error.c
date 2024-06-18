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

void	print_err(const char *cmd, int err)
{
	const char *error_prefix;
	const char *command_not_found;
	const char *is_directory;

	error_prefix = "minishell: ";
	command_not_found = ": command not found\n";
	is_directory = ": is a directory\n";
	write(STDERR_FILENO, error_prefix, strlen(error_prefix));
	write(STDERR_FILENO, cmd, strlen(cmd));
	if (err == ENOENT)
		write(STDERR_FILENO, command_not_found, strlen(command_not_found));
	else if (err == EISDIR)
		write(STDERR_FILENO, is_directory, strlen(is_directory));
	else
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, strerror(err), strlen(strerror(err)));
		write(STDERR_FILENO, "\n", 1);
	}
}
