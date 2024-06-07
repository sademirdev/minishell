#include "minishell.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "termios.h"
#include "unistd.h"

void	set_termios(void)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
		exit((perror("error"), -1));
	if (tcgetattr(STDIN_FILENO, &term) != 0)
		exit((perror("error"), -1));
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		exit((perror("error"), -1));
}

void	signal_handler_ctrl_c(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_signals(void)
{
	set_termios();
	signal(SIGINT, signal_handler_ctrl_c);
}
