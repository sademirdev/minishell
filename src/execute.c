/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:12:34 by abostano          #+#    #+#             */
/*   Updated: 2024/04/04 11:16:16 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/execute.h"
#include <fcntl.h>

//Mainde başlatılacak fonksiyon burası olacak
int	ft_execute(t_token **head, char *envp[])
{
	int		i;
	int		j;

	j = 0;
	i = define_list(head);
	while (j < i)
	{
		j++;
	}
}

void	ft_recursive(t_token **head, char *envp[], int number, int maks)
{
	pid_t	pid;
	int		pipefd[2];
	
	if (number != maks)
	{
		if (pipe(pipefd) == -1)
			error();
		pid = fork();
		if (pid == -1)
			error();
		if (pid == 0)
			ft_recursive(head, envp, number + 1, maks);
		ft_execute_cmd(head, envp, pipefd);
	}
	else
	{
		ft_execute_cmd(head, envp, pipefd);
	}
}

//bu komut chatgpt ile yazıldı ve yukarıdaki fonksiyonun içinde kullanıldı
//bir çok hataya sahip
//AYRICA NORM HATALARI DA VAR
void	ft_execute_cmd(t_token **head, char *envp[], int pipefd[])
{
	// Komut için gerekli değişkenler
    char *cmd = (*head)->data; // İlk token komutu temsil eder
    t_token *arg_token = (*head)->next; // İkinci token argümanları temsil eder

    // Pipe'ı kapat
    close(pipefd[0]);

    // Eğer argüman varsa, komutu ve argümanları execvp fonksiyonuyla çalıştır
    if (arg_token != NULL) {
        // Komutun ve argümanlarının listesi
        char *args[10]; // Argümanlar için bir dizi
        args[0] = cmd; // İlk argüman komuttur
        int i = 1;
        while (arg_token != NULL) {
            args[i] = arg_token->data;
            arg_token = arg_token->next;
            i++;
        }
        args[i] = NULL; // execvp'nin son argümanı NULL olmalıdır

        // Pipe'ı stdout'a yönlendir (write end)
        dup2(pipefd[1], STDOUT_FILENO);

        // execvp çağrısı
        if (execvp(cmd, args) == -1) {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }
    }
    // Argüman yoksa, sadece komutu çalıştır
    else {
        // Pipe'ı stdout'a yönlendir (write end)
        dup2(pipefd[1], STDOUT_FILENO);

        // execvp çağrısı
        if (execlp(cmd, cmd, (char *)NULL) == -1) {
            perror("execlp failed");
            exit(EXIT_FAILURE);
        }
    }
}

int	define_list(t_token **head)
{
	int		i;

	i = 0;
	while (head[i])
		i++;
	return (i);
}