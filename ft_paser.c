/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:08:50 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 02:53:07 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_paser_func(t_tokken_list **tokken, t_val **val)
{
	ft_val_set(val);
	//ft_find_pipe(*tokken, val, pipefd);
	ft_find_redir(tokken, val);
	if ((*val)->here_sig == 1)
		return ;
}

void	ft_heredoc_change(t_tokken_list **tokken)
{
	t_tokken_list	*head;
	char	*doc_name;
	int		i;
	char	*doc_num;

	head = *tokken;
	i = 0;
	
	while (*tokken)
	{
		if (!ft_strncmp((*tokken)->content, "<<", 2))
		{
			i += 1;
			doc_name = ft_strdup("a");
			doc_num = ft_itoa(i);
			free((*tokken)->next->content);
			(*tokken)->next->content = ft_strjoin(doc_name, doc_num);
			free(doc_num);
			(*tokken) = (*tokken)->next;
		}
		if (!(*tokken)->next)
			break;
		(*tokken) = (*tokken)->next;
	}
	*tokken = head;
}

void	ft_paser_manager(t_tokken_list *tokken, char **envp, t_val **val)
{
	pid_t	pid;
	pid_t	pid_here;
	int pipefd[2] = {-1, -1};
	int prev_pipe = -1;
	int status;
	int	here_flag;

	here_flag = 0;
	if (!here_flag)
	{
		set_signal_int_ig();
		pid_here = fork();
		if (pid_here == 0)
		{
			set_signal_int_ex();
			signal(SIGINT, handler_here);
			(*val)->doc_num = 0;
			if (!ft_strncmp(tokken->content, "<<", 2))
			{
				ft_first_heredoc(&tokken, val);
			}
			else
				ft_heredoc(&tokken, val);
			here_flag++;
			exit(1);
		}
		else
		{
			signal(SIGINT, handler_int);
			waitpid(pid_here, &status, 0);
			int	i = 0;
			if (WIFEXITED(status))
			{  // 정상 종료 여부 확인
				i = WEXITSTATUS(status);
				if (i == 1 && signal_flag == 2)
					i = 130;
				else if (i == 1)
					i = 127;
				signal_flag = 0;
				(*val)->exit_code = i;
			}
			else
				printf("Child terminated in an unknown way\n");
			//printf("here1{%d}", (*val)->exit_code);
		}
	}
	if ((*val)->exit_code == 130)
		return ;
	ft_heredoc_change(&tokken);
	// t_tokken_list *lst = tokken;
	// int i = 0;
	// while (lst)
	// {
	// 	printf("lst%d = [%s]\n", i++, lst->content);
	// 	lst = lst->next;
	// }
	set_signal_int_ex();
	while (tokken)
	{
		if (ft_next_pipe(tokken))
		{
			if (pipe(pipefd) == -1)
				error("pipe failed", 1);
		}
		else
		{
			pipefd[0] = -1;
			pipefd[1] = -1;
		}
		ft_paser_func(&tokken, val);
		//printf("플래그값 {%d}, 파일값{%d}", val.here_flag, val.fd_in);
		// if (val.here_flag == 1 && val.fd_in < 0)
		// 	break ;
		pid = fork();
		set_signal_quit_ex();
		signal(SIGQUIT,handler_quit);
		set_signal_int_ig();
		if (pid < 0)
			error("Fork error", 1);
		else if (pid == 0)
		{
			ft_find_cmd(tokken, val);
			set_signal_int_ex();
			printf("fd in값 {%d} fd out값 {%d} token값 {%s}\n", (*val)->fd_in, (*val)->fd_out, tokken->content);
			if (prev_pipe != -1)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			if (pipefd[1] != -1)
			{
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (pipefd[0] != -1)
				close(pipefd[0]);
			ft_dup(val, envp, pipefd);
		}
		else
		{
			signal(SIGINT, handler_int);
			if (prev_pipe != -1)
				close(prev_pipe);
			if (pipefd[1] != -1)
				close(pipefd[1]);
			prev_pipe = pipefd[0];
			(*val)->cmd = NULL; //cmd 초기화
			waitpid(pid, &status, 0);
			int	i = 0;
			if (WIFEXITED(status))
			{  // 정상 종료 여부 확인
				i = WEXITSTATUS(status);
				if (i == 1 && signal_flag == 1)
					i = 130;
				else if (i == 1 && signal_flag == 2)
					i = 131;
				else if (i == 1)
					i = 127;
				signal_flag = 0;
				(*val)->exit_code = i;
			}
			else if (WIFSIGNALED(status))
			{  // 시그널로 종료되었는지 확인
				(*val)->exit_code = WTERMSIG(status) + 128;
			//	printf("Child terminated by signal: %d\n", i);
			}
			else
				printf("Child terminated in an unknown way\n");
			//printf("here1{%d}", (*val)->exit_code);
		}
		while (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) != 0)
		{
			tokken = tokken->next;
		}
		if (tokken && tokken->content && ft_strncmp(tokken->content, "|", 1) == 0)
			tokken = tokken->next;
	}
	if (prev_pipe != -1)
		close(prev_pipe);
	//while (wait(&status) > 0);
	//printf("here2{%d}", (*val)->exit_code);
}
