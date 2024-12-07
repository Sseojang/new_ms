/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_test.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojang <seojang@student.42gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 20:41:23 by seojang           #+#    #+#             */
/*   Updated: 2024/12/07 23:48:18 by seojang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_TEST_H
# define MS_TEST_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

extern volatile int	g_signal_flag;

typedef struct s_flag
{
	int	pipe;
}	t_flag;

typedef struct s_tlist
{
	char			*content;
	struct s_tlist	*next;
}	t_tlist;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_val
{
	int		pipe_flag;
	int		fd_in;
	int		fd_out;
	int		heredoc_fd;
	int		tokken_len;
	int		redir_flag;
	int		tmp_out;
	char	*heredoc;
	int		doc_num;
	int		here_sig;
	int		exit_code;
	char	*home;
	int		prev_pipe;
	t_tlist	*head;
	t_tlist	*cmd;
}	t_val;

typedef struct s_here_val
{
	char	*eof;
	char	*ret;
	char	*temp;
	char	*file;
	char	*doc_name;
	char	*doc_num;
	int		tmpfd;
}	t_here_val;

typedef struct s_word
{
	int			count;
	int			flag;
	int			single_quote_flag;
	int			double_quote_flag;
	int			quote_flag;
	const char	*start;
	const char	*end;
}	t_word;

//libft.c
int		ft_is_digit(char c);
int		ft_is_alpha(char c);

//lst_util.c
t_tlist	*ft_lstnew(char *content);
void	ft_lstadd_back(t_tlist **lst, t_tlist *new);
void	ft_lstclear(t_tlist **lst);

//token
void	ft_tokenizer(char *line, char **envp, t_val *val);
void	ft_in_pipe(char *line, char **envp, t_tlist **tokken, t_val *val);
char	*ft_alpha_digit(char *line, int *i);
char	*ft_double_qoute_check(char *line, int *i, char **envp);
char	*ft_export_ptr(char *line, int *i, char **envp);
char	*ft_export_push(char *temp, char **envp);
char	*ft_single_qoute_check(char *line, int *i);
char	*ft_redirection_check(char *line, int *i);
char	*ft_option(char	*line, int *i);

//utils
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(char const *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

// ft_split.c
char	**split(const char *s, char c, int size, char **p);
char	**ft_split(const char *s, char c);
void	flag1_case(t_word *word, char s, char c);
int		count_words(const char *s, char c);
void	end_of_word(const char **s, char c, t_word *word);

//ft_split_utils.c
void	ft_free(char **p, int sz);
void	init_word(t_word *word);
int		is_quote(const char *s);

//ft_qoute.c
int		ft_double_qoute(char *line, int i, char **envp);
int		ft_single_qoute(char *line, int i);
void	ft_qoute_check(char *line, char **envp, t_val *val);

//ft_export.c
void	ft_print_export(char *temp, char **envp);
int		ft_export_check(char *line, int i, char **envp);

//ft_paser
char	*store_path(char **envp);
char	*find_path(char *argv, const char *env);
void	ft_val_set(t_val **val);
void	error(char *s, int num);
void	execute_cmd(t_tlist *tokken, char **envp);
void	ft_paser_manager(t_tlist *tokken, char **envp, t_val **val);
void	free_path(char **paths);

//redir
void	ft_redir_open(t_tlist *lst, t_val **val, t_tlist **tokken);
void	ft_redir_out(t_tlist *lst, t_val **val, t_tlist **tokken);
void	ft_redir_add(t_tlist *lst, t_val **val, t_tlist **tokken);
void	ft_redir_here(t_tlist *lst, t_val **val, t_tlist **tokken);

void	ft_find_cmd(t_tlist *tokken, t_val **val);
void	ft_dup(t_val **val, char **envp, int *pipe);
void	ft_find_pipe(t_tlist *tokken, t_val *val, int *pipefd);
void	ft_find_redir(t_tlist **tokken, t_val **val);

int		ft_next_pipe(t_tlist *tokken);

//heredoc
void	ft_heredoc(t_tlist **tokken, t_val **val);
void	ft_push_doc(t_tlist **tokken, t_val **val);
void	ft_first_heredoc(t_tlist **tokken, t_val **val);
void	ft_push_first_doc(t_tlist **tokken, t_val **val);

//ft_itoa
char	*ft_itoa(int n);

//ft_signal
void	handler_quit(int sig);
void	handler(int sig);
void	handler_int(int sig);
void	handler_here(int sig);

void	ft_redir_here_util(t_tlist **tokken);
void	ft_redir_add_util(t_tlist **tokken);
void	ft_redir_out_util(t_tlist **tokken);
void	ft_redir_open_util(t_tlist **tokken);

void	ft_here_child(t_tlist **tokken, t_val **val, int *here_flag);
void	ft_here_parents(t_val **val);

void	ft_excute_cmd_util_one(t_tlist *tokken, int *arg_count);
void	ft_excute_cmd_util_two(t_tlist *tokken, int arg_count, char **argv);
void	ft_find_path_set(char *paths, char **path, char *command);

int		ft_find_here(t_tlist *tokken);
void	ft_heredoc_ex(t_tlist **tokken, t_val **val, int *here_flag);

void	ft_child_process(t_tlist *tokken, t_val **val, int (*pipefd)[2], \
char **envp);
void	ft_parents_process(t_val **val, int (*pipefd)[2]);
void	ft_move_token(t_tlist **tokken);

void	ft_here_ex(t_here_val *here_val);
void	ft_wait_child(t_val **val, int *status);

#endif /* MS_TEST_H*/