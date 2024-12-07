/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_util_exe_norm.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 22:54:54 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 23:32:39 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	ft_excute_cmd_util_one(t_tlist *tokken, int *arg_count)
{
	while (tokken && ft_strncmp(tokken->content, "|", 1))
	{
		if (!ft_strlen(tokken->content))
			;
		else
			(*arg_count)++;
		tokken = tokken->next;
	}
}

void	ft_excute_cmd_util_two(t_tlist *tokken, int arg_count, char **argv)
{
	int	i;

	i = 0;
	while (i < arg_count)
	{
		if (!ft_strlen(tokken->content))
			i++;
		else
		{
			argv[i] = ft_strdup(tokken->content);
			tokken = tokken->next;
			i++;
		}
	}
}

void	ft_find_path_set(char *paths, char **path, char *command)
{
	char	*temp;

	temp = NULL;
	temp = ft_strdup(paths);
	*path = ft_strjoin(temp, "/");
	*path = ft_strjoin(*path, command);
}
