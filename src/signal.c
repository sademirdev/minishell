#include "minishell.h"
#include "termios.h"
#include "signal.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"

void	set_termios(void)
{
	struct termios	term1;

	if (tcgetattr(STDIN_FILENO, &term1) != 0)
		exit((perror("error"), -1));
	else
	{
		term1.c_cc[VQUIT] = _POSIX_VDISABLE;
		term1.c_lflag |= ECHOE | ICANON;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
			exit((perror("error"), -1));
		if (tcgetattr(STDIN_FILENO, &term1) != 0)
			exit((perror("error"), -1));
	}
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

void	signal_handler_ctrl_d(int signo)
{
	if (signo == SIGQUIT)
		exit(0);
}

void signals(void)
{
	set_termios();
	signal(SIGINT, signal_handler_ctrl_c);
	signal(SIGQUIT, signal_handler_ctrl_d);
}
