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

#include "../../inc/execute.h"

//Mainde başlatılacak fonksiyon burası olacak
int	ft_execute(t_token **head, char *envp[])
{
	exec_c	**promt;

	promt = init_exec_s(head);
	find_path_of_command(head, envp);

}
