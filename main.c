/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:02:13 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 22:22:09 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

volatile int	g_signal_flag;

void	main_set(char **line, t_val *val)
{
	(*line) = NULL;
	g_signal_flag = 0;
	val->exit_code = 0;
}

void	main_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	signal(SIGINT, handler);
}

void	flag_check(t_val *val)
{
	if (g_signal_flag == 1)
	{
		g_signal_flag = 0;
		val->exit_code = 130;
	}
}

void	line_null(void)
{
	write(1, "exit\n", 5);
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	t_val	val;

	(void)ac;
	(void)av;
	main_set(&line, &val);
	while (1)
	{
		main_signal();
		line = readline("minishell>");
		if (line == NULL)
			line_null();
		else if (!ft_strlen(line))
			;
		else if (line)
		{
			add_history(line);
			ft_tokenizer(line, envp, &val);
		}
		flag_check(&val);
		free(line);
		line = NULL;
	}
	return (0);
}
