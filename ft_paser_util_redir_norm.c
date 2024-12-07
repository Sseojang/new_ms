/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_util_redir_norm.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:51:49 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 21:01:10 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_redir_open_util(t_tlist **tokken)
{
	int	i;

	i = 0;
	while ((*tokken) && ft_strncmp((*tokken)->content, "<", 1))
		(*tokken) = (*tokken)->next;
	while ((*tokken) && ft_strncmp((*tokken)->content, "|", 1))
	{
		free((*tokken)->content);
		(*tokken)->content = ft_strdup("");
		(*tokken) = (*tokken)->next;
		i++;
		if (i == 2)
			break ;
	}
}

void	ft_redir_out_util(t_tlist **tokken)
{
	int	i;

	i = 0;
	while ((*tokken) && ft_strncmp((*tokken)->content, ">", 1))
		(*tokken) = (*tokken)->next;
	while ((*tokken) && ft_strncmp((*tokken)->content, "|", 1))
	{
		free((*tokken)->content);
		(*tokken)->content = ft_strdup("");
		(*tokken) = (*tokken)->next;
		i++;
		if (i == 2)
			break ;
	}
}

void	ft_redir_add_util(t_tlist **tokken)
{
	int	i;

	i = 0;
	while ((*tokken) && ft_strncmp((*tokken)->content, ">>", 2))
		(*tokken) = (*tokken)->next;
	while ((*tokken) && ft_strncmp((*tokken)->content, "|", 1))
	{
		free((*tokken)->content);
		(*tokken)->content = ft_strdup("");
		(*tokken) = (*tokken)->next;
		i++;
		if (i == 2)
			break ;
	}
}

void	ft_redir_here_util(t_tlist **tokken)
{
	int	i;

	i = 0;
	while ((*tokken) && ft_strncmp((*tokken)->content, "<<", 2))
		(*tokken) = (*tokken)->next;
	while ((*tokken) && ft_strncmp((*tokken)->content, "|", 1))
	{
		free((*tokken)->content);
		(*tokken)->content = ft_strdup("");
		(*tokken) = (*tokken)->next;
		i++;
		if (i == 2)
			break ;
	}
}
