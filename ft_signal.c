/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 20:59:56 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 22:20:37 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	handler_here(int sig)
{
	if (sig == SIGINT)
	{
		g_signal_flag = 1;
		write(1, "\n", 1);
		exit(1);
	}
}

void	handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_signal_flag = 1;
	write(1, "minishell>\n", 11);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
