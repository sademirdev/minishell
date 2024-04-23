#include "../../inc/execute.h"

void	workit(exec_c **head)
{
	/*
	Bu fonksiyon diğer fonksiyonda kullandığımız pipe yapısını
	initialize eder ve diğer fonksiyonu başlatır. Okunabilirlik
	ve işlevsellik açısından work_one_part fonksiyonundan ayrı.
	*/
	exec_c	*tmp;
	int		pipefd[2];

	work_one_part(tmp, pipefd);

}

void	work_one_part(exec_c *head, int pipefd[])
{
	/*
	Bu fonksiyonun temel amacı kurduğumuz exec_c structındaki
	parçalardan her birini recursive bir şekilde çalıştırmaktır.
	Her bir işlem için ayrı bir pipe açmak yerine tek bir pipe
	ile hepsinin bağlantısı sağlanmıştır. Eğerki komutta bir
	dosya varsa bunun açılması sağlanmıştır.
	*/
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
	else
	{
		dup2(pipefd[1], STDOUT_FILENO);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	execve(head->path, head->full_command, NULL);
	if (childpid != 0)
		work_one_part(head->next, pipefd);
}