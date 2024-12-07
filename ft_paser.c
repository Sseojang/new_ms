/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:08:50 by seojang           #+#    #+#             */
/*   Updated: 2024/12/08 00:32:37 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_paser_func(t_tlist **tokken, t_val **val)
{
	ft_val_set(val);
	ft_find_redir(tokken, val);
}

void	ft_before_fork(t_tlist *tokken, int (*pipefd)[2])
{
	if (ft_next_pipe(tokken))
	{
		if (pipe(*pipefd) == -1)
			error("pipe failed", 1);
	}
	else
	{
		(*pipefd)[0] = -1;
		(*pipefd)[1] = -1;
	}
}

void	ft_siganl_set(void)
{
	signal(SIGQUIT, SIG_DFL);
	signal(SIGQUIT, handler_quit);
	signal(SIGINT, SIG_IGN);
}

void	ft_wait_pipe(t_val **val)
{
	int	status;

	while (wait(&status) > 0)
		ft_wait_child(val, &status);
}

void	ft_paser_manager(t_tlist *tokken, char **envp, t_val **val)
{
	pid_t	pid;
	int		pipefd[2];
	int		here_flag;

	(*val)->prev_pipe = -1;
	here_flag = 0;
	if (!here_flag && ft_find_here(tokken))
		ft_heredoc_ex(&tokken, val, &here_flag);
	while (tokken)
	{
		ft_before_fork(tokken, &pipefd);
		ft_paser_func(&tokken, val);
		pid = fork();
		ft_siganl_set();
		if (pid < 0)
			error("Fork error", 1);
		else if (pid == 0)
			ft_child_process(tokken, val, &pipefd, envp);
		else
			ft_parents_process(val, &pipefd);
		ft_move_token(&tokken);
	}
	if ((*val)->prev_pipe != -1)
		close((*val)->prev_pipe);
	ft_wait_pipe(val);
}
