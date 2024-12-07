/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_here_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 21:53:26 by seojang           #+#    #+#             */
/*   Updated: 2024/12/08 00:20:14 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_here_child(t_tlist **tokken, t_val **val, int *here_flag)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, handler_here);
	(*val)->doc_num = 0;
	if (!ft_strncmp((*tokken)->content, "<<", 2))
		ft_first_heredoc(tokken, val);
	else
		ft_heredoc(tokken, val);
	(*here_flag)++;
	exit(1);
}

void	ft_here_parents(t_val **val)
{
	int	status;

	signal(SIGINT, handler_int);
	while (wait(&status) > 0)
	{
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1 && g_signal_flag == 2)
			{
				(*val)->exit_code = 130;
				return ;
			}
			else if (WEXITSTATUS(status) == 1)
				(*val)->exit_code = 127;
			g_signal_flag = 0;
		}
	}
}

int	ft_find_here(t_tlist *tokken)
{
	while (tokken)
	{
		if (!ft_strncmp(tokken->content, "<<", 2))
			return (1);
		tokken = tokken->next;
	}
	return (0);
}

void	ft_heredoc_change(t_tlist **tokken)
{
	t_tlist	*head;
	char	*doc_name;
	char	*doc_num;
	int		i;

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
			break ;
		(*tokken) = (*tokken)->next;
	}
	*tokken = head;
	signal(SIGINT, SIG_DFL);
}

void	ft_heredoc_ex(t_tlist **tokken, t_val **val, int *here_flag)
{
	pid_t	pid_here;

	signal(SIGINT, SIG_IGN);
	pid_here = fork();
	if (pid_here == 0)
		ft_here_child(tokken, val, here_flag);
	else
		ft_here_parents(val);
	ft_heredoc_change(tokken);
}
