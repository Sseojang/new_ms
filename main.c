/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 19:02:13 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 02:54:22 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

int	signal_flag;

void	handler(int sig)
{
	if (sig != SIGINT)
		return ;
	signal_flag = 1;
	write(1, "minishell>\n", 11);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handler_here(int sig)
{
	if (sig == SIGINT)
	{
		signal_flag = 1;
		write(1, "\n", 1);
		exit(1);
	}
}

void	handler_fork(int sig)
{
	if (sig != SIGINT)
		return ;
	signal_flag = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int main(int ac, char **av, char **envp)
{
	char	*line;
	t_val	val;

	line = NULL;
	(void)ac;
	(void)av;
	signal_flag = 0;
	val.exit_code = 0;
	while (1)
	{
		set_signal_quit_ig();
		set_signal_int_ex();
		signal(SIGINT,handler);
		line = readline("minishell>");
		if (line == NULL)
		{
			write(1, "exit\n", 5);
			//printf("현재 프로세스 아이디 {%d}", getpid());
			break ;
		}
		if (!ft_strlen(line))
		{
			free(line);
			line = NULL;
			continue ;
		}
		if (line)
		{
			add_history(line);
			ft_tokenizer(line, envp, &val);
			free(line);
			line = NULL;
		}
		if (signal_flag == 1)
		{
			signal_flag = 0;
			val.exit_code = 130;
		}
	}
	return (0);
}