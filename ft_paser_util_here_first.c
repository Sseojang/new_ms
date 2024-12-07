/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_util_here_first.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:26:57 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 23:44:47 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_first_heredoc(t_tlist **tokken, t_val **val)
{
	t_tlist	*head;

	head = (*tokken);
	while (*tokken && (*tokken)->next)
	{
		if (!ft_strncmp((*tokken)->content, "<<", 2))
			ft_push_first_doc(tokken, val);
		(*tokken) = (*tokken)->next;
	}
	(*tokken) = head;
}

void	ft_here_first_util(t_here_val *here_val, t_tlist *tokken, t_val **val)
{
	(*val)->doc_num += 1;
	here_val->doc_name = ft_strdup("a");
	here_val->doc_num = ft_itoa((*val)->doc_num);
	here_val->doc_name = ft_strjoin(here_val->doc_name, here_val->doc_num);
	free(here_val->doc_num);
	here_val->file = ft_strdup(here_val->doc_name);
	here_val->eof = ft_strdup(tokken->next->content);
	here_val->temp = NULL;
	here_val->ret = NULL;
}

void	ft_here_free_first_set(t_here_val *here_val, t_tlist **tokken)
{
	here_val->tmpfd = open(here_val->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write(here_val->tmpfd, here_val->ret, ft_strlen(here_val->ret));
	close(here_val->tmpfd);
	free((*tokken)->next->content);
	(*tokken)->next->content = ft_strdup(here_val->file);
	free(here_val->file);
	free(here_val->eof);
	free(here_val->ret);
	free(here_val->doc_name);
}

void	ft_push_first_doc(t_tlist **tokken, t_val **val)
{
	t_here_val	here_val;

	ft_here_first_util(&here_val, *tokken, val);
	ft_here_ex(&here_val);
	ft_here_free_first_set(&here_val, tokken);
}
