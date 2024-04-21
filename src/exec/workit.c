#include "../../inc/execute.h"

void	workit(exec_c **head)
{
	exec_c	*tmp;
	int		pipefd[2];

	work_one_part(tmp, pipefd);

}

void	work_one_part(exec_c *head, int pipefd[])
{
	pid_t	childpid;
	int		fd;

	fd = 0;
	if (head->next != NULL)
		childpid = fork();
	if (head->file != NULL)
	{
		fd = open(head->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(fd, STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	execve(head->path, head->args, NULL);
	/*
	Bu kısım fonksiyonumuzu recursive bir şekilde çalıştırmaya devam ediyor.
	Eğer bir devam yapısı yoksa zaten fork çalışmadığı için bir değer sıfırdan
	farklı olmakta.Ve bu sayede fonksiyon çalışmayı kesmekte.
	*/
	if (childpid != 0)
		work_one_part(head->next, pipefd);
}