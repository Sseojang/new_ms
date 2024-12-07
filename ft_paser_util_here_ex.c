/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_util_here_ex.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:39:04 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 22:50:11 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_here_ex_norm(t_here_val *here_val, int i)
{
	if (!i)
		here_val->ret = ft_strdup("");
	free(here_val->temp);
	here_val->temp = NULL;
}

void	ft_here_ex_norm_second(t_here_val *here_val)
{
	if (ft_strncmp(here_val->temp, "\n", 1))
		here_val->temp = ft_strjoin(here_val->temp, "\n");
	if (!here_val->ret)
		here_val->ret = ft_strdup(here_val->temp);
	else
		here_val->ret = ft_strjoin(here_val->ret, here_val->temp);
}

void	ft_here_ex(t_here_val *here_val)
{
	int	i;

	i = 0;
	while (1)
	{
		here_val->temp = readline(">");
		if (here_val->temp && \
		!ft_strncmp(here_val->temp, here_val->eof, ft_strlen(here_val->eof)))
		{
			ft_here_ex_norm(here_val, i);
			break ;
		}
		else if (here_val->temp == NULL)
		{
			printf("경고 %s가 행의 마지막 열에 없습니다\n", here_val->eof);
			ft_here_ex_norm(here_val, i);
			break ;
		}
		ft_here_ex_norm_second(here_val);
		i++;
		free(here_val->temp);
		here_val->temp = NULL;
	}
}
