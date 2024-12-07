/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paser_util_exe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:13:15 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 23:29:50 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_test.h"

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
	paths = NULL;
}

void	ft_find_cmd(t_tlist *tokken, t_val **val)
{
	while (tokken && ft_strncmp(tokken->content, "|", 1) != 0)
	{
		if (tokken->content != NULL && ft_strlen(tokken->content) != 0)
		{
			(*val)->cmd = tokken;
			return ;
		}
		tokken = tokken->next;
	}
	exit(1);
}

char	*store_path(char **envp)
{
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = envp[i] + 5;
		i++;
	}
	return (path);
}

char	*find_path(char *argv, const char *env)
{
	char	**paths;
	char	*command;
	char	*path;
	int		i;

	paths = ft_split(env, ':');
	command = ft_strdup(argv);
	i = 0;
	if (access(command, F_OK | X_OK) == 0)
		path = ft_strdup(command);
	else
	{
		while (paths[i])
		{
			ft_find_path_set(paths[i++], &path, command);
			if (access(path, F_OK | X_OK) == 0)
				break ;
			free(path);
			path = NULL;
		}
	}
	free_path(paths);
	free(command);
	return (path);
}

void	execute_cmd(t_tlist *tokken, char **envp)
{
	char *const	env[] = {store_path(envp), NULL};
	char		**argv;
	char		*path;
	int			arg_count;

	arg_count = 0;
	ft_excute_cmd_util_one(tokken, &arg_count);
	argv = malloc(sizeof(char *) * (arg_count + 1));
	if (!argv)
		error("Memory allocation failed", 2);
	ft_excute_cmd_util_two(tokken, arg_count, argv);
	argv[arg_count] = NULL;
	path = find_path(argv[0], env[0]);
	if (!path)
		error(argv[0], 3);
	execve(path, argv, envp);
	error("execve failed", 2);
}
