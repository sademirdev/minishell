#include "minishell.h"
#include "signal.h"

void	signal_handler_ctrl_c(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signal_handler_ctrl_slash(int signo)
{
	if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 1);
	}
}

void	signal_handler_ctrl_z(int signo)
{
	if (signo == SIGTSTP)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void signals(void)
{
	signal(SIGINT, signal_handler_ctrl_c);
	signal(SIGQUIT, signal_handler_ctrl_slash);
	signal(SIGTSTP, signal_handler_ctrl_z);
}
