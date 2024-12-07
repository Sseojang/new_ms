/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_man_util.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:00:01 by seojang           #+#    #+#             */
/*   Updated: 2024/12/08 00:35:41 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_move_token(t_tlist **tokken)
{
	while ((*tokken) && (*tokken)->content && \
	ft_strncmp((*tokken)->content, "|", 1) != 0)
		(*tokken) = (*tokken)->next;
	if ((*tokken) && (*tokken)->content && \
	ft_strncmp((*tokken)->content, "|", 1) == 0)
		(*tokken) = (*tokken)->next;
}

void	ft_parents_process(t_val **val, int (*pipefd)[2])
{
	signal(SIGINT, handler_int);
	if ((*val)->prev_pipe != -1)
		close((*val)->prev_pipe);
	if ((*pipefd)[1] != -1)
		close((*pipefd)[1]);
	(*val)->prev_pipe = (*pipefd)[0];
	(*val)->cmd = NULL;
}

void	ft_child_process(t_tlist *tokken, t_val **val, \
int (*pipefd)[2], char **envp)
{
	ft_find_cmd(tokken, val);
	signal(SIGINT, SIG_DFL);
	if ((*val)->prev_pipe != -1)
	{
		dup2((*val)->prev_pipe, STDIN_FILENO);
		close((*val)->prev_pipe);
	}
	if ((*pipefd)[1] != -1)
	{
		dup2((*pipefd)[1], STDOUT_FILENO);
		close((*pipefd)[1]);
	}
	if ((*pipefd)[0] != -1)
		close((*pipefd)[0]);
	ft_dup(val, envp, (*pipefd));
}

void	ft_wait_child(t_val **val, int *status)
{
	(*val)->exit_code = 0;
	if (WIFEXITED(*status))
	{
		(*val)->exit_code = WEXITSTATUS(*status);
		if ((*val)->exit_code == 1 && g_signal_flag == 1)
			(*val)->exit_code = 130;
		else if ((*val)->exit_code == 1 && g_signal_flag == 2)
			(*val)->exit_code = 131;
		else if ((*val)->exit_code == 1)
			(*val)->exit_code = 127;
		else
			(*val)->exit_code = 0;
		g_signal_flag = 0;
	}
	else if (WIFSIGNALED(*status))
		(*val)->exit_code = WTERMSIG(*status) + 128;
}
