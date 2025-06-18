/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sradosav <sradosav@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:31:47 by mzutter           #+#    #+#             */
/*   Updated: 2025/06/18 19:37:01 by sradosav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdbool.h>
# include "libft/libft.h"

# define MAX_FD 1023
# define MAX_HEREDOC 16
# define OPEN_QUOTES "Minishell does not support open quotes,\
						please escape them properly\n"
# define DOUBLE_DOLLARS "Minishell ne gere pas $$\n"
# define AMB_REDIR "Ambiguous redirect: "

typedef enum e_token_type
{
	WORD, //0
	PIPE, //1
	IN, //2
	OUT, //3
	APPEND, //4
	HDOC, //5
	FD, // 6
	CMD, // 7
	ARG, // 8
	LIMITER, // 9
	FILEN, // 10
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	int				rank;
	char			*value;
	struct s_token	*next;
	bool			amb_redir;
}	t_token;

typedef struct s_quote_state
{
	int		w_start;
	bool	in_quotes;
	char	opening_quote;
}	t_quote_state;

typedef struct s_input_context
{
	char	*str;
	int		rank;
}	t_input_context;

typedef struct s_envvar
{
	char			*var;
	int				exported;
	struct s_envvar	*next;
}	t_envvar;

typedef struct s_shell
{
	char		**env_arr;
	t_envvar	*env;
	t_token		*token;
	char		**splitted;
	int			exit_status;
}	t_shell;

typedef struct s_expand
{
	int		i;
	int		j;
	int		count;
	int		start;
	bool	in_single_quote;
	bool	in_double_quote;
	char	**result;
}	t_expand;

typedef struct s_splitter
{
	size_t	start;
	size_t	capacity;
	size_t	i;
	size_t	count;
}	t_splitter;

//booleans functions for split2
bool		is_quote(char c);
bool		is_closing_quote(char c, char opening_quote);
bool		handle_quotes(char c, bool *in_quotes, char *opening_quote);
bool		is_whitespace(char c);

//string_utils functions
char		*ft_substrword(char *str, int start, int end);
char		*trim_quotes(char *str);
char		**ft_strdup_array(char **src);
char		*ft_strncpy(char *dest, const char *src, unsigned int n);
char		*strndup_custom(const char *s, size_t n);
int			count_strings(char **arr);
void		ft_init_var(size_t *i, size_t *count, bool *in_quotes, char *c);
void		whitespace_to_space(char *str);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strndup(const char *s, size_t n);

//misc utils
void		*ft_realloc(void *ptr, int old_size, int new_size);

//env utils
int			env_var_exists(char *var, t_shell *shell);
void		update_env(char *var, char *str, t_shell *shell);
void		update_or_add(char *var, char *str, t_shell *shell, int exported);
char		*ft_getenv(char *var, t_shell *shell);
t_envvar	*ft_env_to_list(char **envp);
t_envvar	*copy_env_list(t_envvar *env);
void		ft_sort_env_list(t_envvar *head);
void		free_env_list(t_envvar **head);
int			add_env_var(t_envvar **head, char *str, int exported, t_shell *s);
void		free_env_list(t_envvar **head);

//parsing utils
int			ft_has_invalid_quotes(const char *str);

//main lexer functions
char		**ft_split2(char const *s, char c);
void		tokenizer(t_shell *shell, int rank);
void		refine_token_type(t_token *token);
void		second_refine_token_type(t_token *token);

//linked_list_utils functions
t_token		*create_token(char *str);
int			add_token(t_shell *shell, char *str, t_token_type type, int rank);

//clean exit
void		ft_free_str_array(char **arr);
void		free_list(t_token **head);
void		ft_clean_exit(char *input, t_shell *shell);

//expand
void		expand(t_shell *shell);
int			ft_count_segments(const char *input);
char		**split_and_expand(const char *input);
char		*join_chars(char **str);
void		case_only_dollar(t_expand *ex);
void		case_question_mark(t_expand *ex);
void		case_env_var(t_expand *ex, const char *input);

//tmp
char		**split_keep_separators(const char *s, bool (*is_sep)(char));

#endif