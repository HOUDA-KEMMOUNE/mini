/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akemmoun <akemmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 15:59:11 by hkemmoun          #+#    #+#             */
/*   Updated: 2025/06/26 11:41:16 by akemmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
// #include <limits.h>
# include "./libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
// #include "./get_next_line/get_next_line.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

// #include <readline/history.h>

typedef enum e_token_type
{
	WORD,
	FILE_NAME,
	CMD,
	DELIMITER,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
}						t_token_type;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	char				quote;
	struct s_token		*next;
}						t_token;

// to call builtins
typedef int	(*t_builtin_ptr)(t_token *, t_env **);
typedef struct s_built
{
	char					*cmd;
	t_builtin_ptr			ptr;
}						t_built;

typedef struct s_meta_char
{
	char				*value;
	t_token_type		type;
}						t_meta_char;

// 3la 9bal redirections o dak tkharbi9
typedef struct s_token_exc
{
	char				*value;
	char				*cmd;
	char				*cmd_path;
	char				**args;
	char				*file;
	char				**delimiter;
	char				**heredoc_file;
	int					count_heredoc;
	int					count_cmd;
	int					fd_in;
	int					fd_out;
	// t_token_type		type;
	struct s_token_exc	*next;
}						t_token_exc;

/*------------data structures---------------*/
typedef struct s_shell_data
{
	t_env		*env_list;
	t_token		*tokens;
	t_token_exc	*tokens_exec;
}						t_shell_data;

// typedef struct s_echo
// {
// 	int					fd;
// 	char				*file;
// 	char				*input;
// 	char				**msg;
// }						t_echo;

// to call builtins
// typedef struct s_built
// {
//     char *cmd;
//     int (*ptr)(t_token *tokens, t_env *env);
// } t_built;
// globel env
t_env					**env_func(void);
int						*exit_status_func(void);

/*-------------------lexer utils-------------------*/
int						handle_quoted_word(char *input, int *i,
							t_token **token_list);
void					handle_regular_word(char *input, int *i,
							t_token **token_list);
void					handle_double_operator(char *input, int *i,
							t_token **token_list);
void					handle_single_operator(char *input, int *i,
							t_token **token_list);
int						syntax_err_msg(t_token **token,
							t_token_exc **commande);
void					assign_token_type(t_token **token_list,
							t_meta_char *arr);
void					char_to_str(char c, int n, t_token **token_list);

/*-------------------lexer helper-------------------*/
int						process_operators(char *input, int *i,
							t_token **token_list);
void					handle_redirection_tokens(t_token **token,
							t_token_exc **commande);

/*-------------------errors-------------------*/
int						is_quote_closed(char *input, char quote, int start);
void					print_error(char *msg);
void					print_error_command(t_token **token);
void					print_echo_error(void);

/*-------------------env-------------------*/
void					free_env_array(char **envp);
void					init_minimal_env(t_env **env_list);

/*-------------------Lexer-------------------*/
t_token					*lexer(char *input);
int						word_case(char *input, int *i, t_token **token_list);
void					add_token(t_token **head, char *value,
							t_token_type type, char quote);
void					retype_lexer(t_token **token, t_token_exc **commande);
int						syntax_err_msg(t_token **token, t_token_exc **commande);
void					char_to_str(char c, int n, t_token **token_list);
void					add_type(t_token **token_list);
void					skip_whitespace(char *input, int *i);
int						is_operator(char *input, int i);
int						process_token(char *input, int *i, \
						t_token **token_list);

/*-------------------Parsing-------------------*/
void					parsing(char *input, t_token **token,
							t_env *env_list);
int						se_redirections(t_token **token);
int						check_first_cmd(t_token_exc *token_list);
// void					ft_data_init(t_echo **echo_struct);
void					ft_cd(t_token **token, t_env *env_list);
void					ft_ls(t_token **token, t_env *env_list);
void					ft_export(t_token **token);
void					ft_unset(t_token **token);
int						is_notforbidden_char(char c, int is_first);
int						check_commande(char *input);
void					ft_count(char *s, int *count);
void					ft_count_dotes(t_token **token);
void					ft_env(t_token **token, t_env *env_list);
void					ft_exit(t_token **token);

/*-------------------expander-------------------*/
t_token					*expander(t_token *token_list, t_env *env_list);
t_token					*echo_expander(t_token *token_list, t_env *env_list,
							int fd);
char					*expand_variable(char *value, t_env *env_list);

/*-------------------execution-------------------*/
t_env					*create_env_list(char **envp);
char					*get_env_value(t_env *env, char *key);
void					get_env(t_env *env_list);
void					ft_pwd(t_token **token);
t_token_exc				*tokens_exc_handler(t_token *token);
// void					echo(t_token **token, t_echo **echo_struct,
// 							t_env *env_list);

/*-------------------echo helpers-------------------*/
void					echo(t_token **token, t_token_exc **command);
void					echo_helper(int *i, t_token_exc **command);
int						check_simple_echo(t_token **token,
							t_token_exc **command);
int						check_echo_flag(char *s);
int						echo_builtin(t_token *tokens, t_env **env_list);

/*-------------------export-------------------*/
int						export_internal(t_token *tokens, t_env **env_list);
int						export_builtin_adapter(t_token *tokens,
							t_env **env_list);
void					export_set_var(t_env **env_list, \
						char *key, char *value);
void					export_print_sorted(t_env *env_list);
void					export_print_sorted_helper(t_env **arr, int count);
void					execute_export_args(t_token *current, t_env **env_list);
int						is_valid_identifier(const char *str);
int						cmp_env(t_env *a, t_env *b);

/*-------------------env-------------------*/
int						env_builtin(t_token *tokens, t_env **env_list);

/*-------------------unset-------------------*/
int						unset(t_token *tokens, t_env **env_list);
void					unset_env_var(t_env **env, const char *name);

/*-------------------helpers-------------------*/
int						ft_strcmp(const char *s1, const char *s2);
void					ft_envadd_back(t_env **lst, t_env *new);
void					ft_append(t_token **token);
void					add_token_exc_to_list(t_token_exc **token_list,
							t_token_exc *new);
int						check_echo_flag(char *s);

/*-------------------signals-------------------*/
void					handler_sigint(int sig_num);
void					handler_sigint_child(int sig_num);
void					sig_quit_handler(int sig_num);

/*----------------get_next_line-----------------*/
char					*get_next_line(int fd);
char					*rest_char(char *line);
char					*get_line(char *buffer, char *rest, int fd);
// int		ft_signals(void);

/*----------------builtins-----------------*/
int						run_builtin(char *cmd, t_token *tokens,
							t_env **env_list);

/*----------------free-----------------*/
void					free_env_list(t_env *env);
void					free_token_list(t_token *tok);
void					free_token_exc_list(t_token_exc *cmd);
void					free_delimiter_array(t_token_exc *cmd);
void					free_heredoc_file_array(t_token_exc *cmd);
void					free_heredoc_arrays(t_token_exc *cmd);
void					minishell_cleanup(t_env *env, t_token *tokens,
							t_token_exc *tokens_exec);
void					free_args(char **arr);

/*----------------cd-----------------*/
char					**token_to_args(t_token *tokens);
int						cd(t_token *tokens, t_env **env_list);
int						ft_cd_exec(t_token **tokens, t_env *env_list);
char					*determine_path(t_token *tokens, t_env *env_list,
							char **to_free);
int						handle_basic_cd(const char *path, t_env **env_list);
char					*expand_tilde(const char *path, t_env *env_list);
int						handle_cd_dash(t_env **env_list);
int						is_whitespace_only(const char *str);

// void    pwd(t_token **token);

/*----------------pwd-----------------*/
int						pwd(t_token *tokens, t_env **env_list);

/*------------tokens_exec_helper1---------------*/
void					tokens_exc_helper(t_token **token,
							t_token_exc **token_list);
void					tokens_exc_helper1(t_token_exc **new, t_token **token);
void					tokens_exc_helper2(t_token_exc **new,
							t_token_exc **token_list);
void					handle_heredoc_token(t_token **token);
int						ft_count_args(t_token *token);
void					tokens_exc_redio(t_token *token,
							t_token_exc **token_list);
void					filename_node(t_token **token);
void					fill_args(t_token **token, char **args_tmp,
							int count_args);
void					command_node(t_token **token, t_token_exc **new);

/*------------cmd_paths---------------*/
void					path(t_token_exc **token_list);
int						is_builtin(t_token_exc **token_list);
char					**split_path(void);
char					*find_path(void);
void					simple_cmd(t_token *token, t_token_exc **token_cmd);
void					check_fd(t_token_exc **token_cmd);
char					**env_to_array(t_env *env_list);
// void	env_to_array_helper(t_env *env_list);
int						env_size(t_env *env_list);
void					free_split_path(char **splited_path);
int						set_cmd_path(char **splited_path,
							char *new_cmd, t_token_exc **token_list);
void					print_cmd_error(const char *cmd);

/*------------heredoc---------------*/
void					heredoc(t_token **token, t_token_exc **command);
int						check_heredoc(t_token **token, t_token_exc **command);
int						creat_tmpfile(char **file_name);
void					fill_heredoc_file(int fd, char *delimiter);
void					process_heredoc_line(int fd, char *line, \
						t_env *env_list);
void					setup_heredoc_arrays(t_token_exc *command_tmp);
void					collect_delimiters(t_token *token_tmp, \
						t_token_exc *command_tmp);
void					create_heredoc_files(t_token_exc *command_tmp);

/*------------pipes---------------*/
int						pipes(t_token **token, t_token_exc **command, \
						t_env *env_list);
int						check_pipe(t_token **token);
int						count_cmd(t_token_exc **command);
void					execute_pipeline_command(t_token_exc *cmd, \
						char **envp, t_env **env_list);
void					close_all_pipes(int pipe_fds[][2], int pipe_count);
void					close_unused_pipes(int pipe_fds[][2], \
						int pipe_count, int cmd_index);
void					setup_child_pipes(t_token_exc *cmd, \
						int pipe_fds[][2], int cmd_index, int pipe_count);
int						wait_for_children(pid_t pids[], int count);
int						create_pipes(int pipe_fds[][2], int count);
int						execute_pipeline(int pipe_fds[][2], pid_t pids[], \
						t_token_exc *cmd_current, int count);
int						handle_fork_error(int pipe_fds[][2], int count, \
						pid_t pids[], int i);
void					setup_file_descriptors(t_token_exc *cmd);
void					create_builtin_args(t_token *builtin_token, \
						t_token_exc *cmd);
void					execute_builtin(t_token_exc *cmd, t_env **env_list);
void					execute_external(t_token_exc *cmd, char **envp);

/*------------redirections---------------*/
void					change_redout(t_token **token, t_token_exc **command);
void					check_redirections(t_token **token, \
						t_token_exc **command);
void					check_pipeline_redirections(t_token **token, \
						t_token_exc **command);
void					apply_redirections_for_command_range(t_token *start, \
						t_token *end, t_token_exc *command);
void					apply_redirections_to_command(t_token *cmd_tokens, \
						t_token_exc *command);
void					open_file(int *fd, t_token **redir_token, \
						t_token **token_tmp);

/*------------SC helpers---------------*/
void					simple_cmd_parent(t_token_exc **token_cmd,
							char **envp, int status);
void					simple_cmd_child(t_token_exc **token_cmd, char **envp);
void					handle_word_token(t_token **token, char **args_tmp,
							int *i, int *flag);

/*------------cd helpers---------------*/
void					print_cd_error(const char *arg, int error_type);
void					print_cd_error2(const char *arg, int error_type);
void					update_env(t_env *env, char *key, char *new_value);
int						ft_isspace(int c);

/*------------minishell helpers---------------*/
void					init_shell_vars(t_shell_data *data);
int						handle_empty_input(char **line);
void					cleanup_resources(char **line, t_token **tokens,
							t_token_exc **tokens_exec);

/*------------command processing---------------*/
void					process_input_line(char *line, t_shell_data *data);
int						handle_command_execution(t_shell_data *data,
							char *line);
int						process_command_line(char *line, t_shell_data *data);

/*------------shell loop---------------*/
void					init_environment(char **envp, t_env **env_list);
int						handle_eof_input(char *line, t_shell_data *data);
void					run_shell_loop(t_shell_data *data);

#endif
