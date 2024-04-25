/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abostano <abostano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 16:12:34 by abostano          #+#    #+#             */
/*   Updated: 2024/04/25 14:12:25 by abostano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/execute.h"

//Mainde başlatılacak fonksiyon burası olacak
int	ft_execute(t_token **head, char *envp[])
{
	exec_c	**promt;

	promt = (exec_c **)malloc(sizeof(exec_c *));
	*promt = NULL;
	promt = init_exec_s(head, promt);
	find_path_of_command(promt, envp);
	printf("cmd: %s\n", (*promt)->cmd);
	//workit(promt);
	return (0);
}
