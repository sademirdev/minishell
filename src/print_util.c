#include "minishell.h"
#include <unistd.h>

void	dprint(int fd, const char *s)
{
	write(fd, s, ft_strlen(s));
}

void	dprintln(int fd, const char *s)
{
	dprint(fd, s);
	dprint(fd, ENDL);
}

void	eprint(const char *str)
{
	dprint(STDERR_FILENO, str);
}

void	eprintln(const char *str)
{
	dprintln(STDERR_FILENO, str);
}
