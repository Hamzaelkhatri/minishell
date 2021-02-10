/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 12:43:41 by sqatim            #+#    #+#             */
/*   Updated: 2021/02/10 19:02:48 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <sys/types.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <limits.h>
# include "get_next_line.h"
# define DEBUG_BOOL 0
# define FLAG S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR

int				g_var;
int				g_var1;

typedef struct	s_key
{
	int cntrd;
	int cntrc;
}				t_key;

typedef struct	s_env
{
	char	**fullenv;
	char	*pwd;
	char	*oldpwd;
}				t_env;

typedef struct	s_path
{
	char	*path;
	char	*file1;
	char	*file2;
	int		dollar;
	t_key	*key;
	char	*cmds;
	char	*pathcmd;
	t_env	*env;
}				t_path;

typedef struct	s_cmd
{
	int	echo;
	int	pwd;
	int	exit;
	int	env;
	int	export;
	int	unset;
	int	cd;
}				t_cmd;

typedef struct s_save
{
	int check;
	char *cmd_arg;
	char *file;
	int check_io;
	int result;
	char *red;
	struct s_save *next;
}				t_save;

typedef struct	s_redirection
{
	char	*i_o;
	char	*file;
}				t_redirection;

typedef struct	s_check
{
	int	cmd;
	int	word;
	int	redirection;
}				t_check;

typedef struct	s_tool
{
	char	**tab;
	int		i;
	int		result;
	int		check_io;
	int		indice;
	int		cmd;
	int		argument;
	int		redirection;
}				t_tool;

typedef struct	s_elements
{
	int				indice;
	char			*cmd;
	char			*argument;
	t_redirection	redirection;
}				t_elements;

typedef struct	s_simple_command
{
	t_elements				*l_element;
	struct s_simple_command	*parent;
	struct s_simple_command	*right;
}				t_simple_command;

typedef struct	s_command
{
	t_tool				tool;
	t_simple_command	*s_left;
	struct s_command	*right;
}				t_command;

typedef struct	s_list_cmd
{
	t_command			*command;
	char				*line;
	struct s_list_cmd	*next;
	struct s_list_cmd	*previous;
}				t_list_cmd;

typedef struct	s_tmp
{
	t_list_cmd			*lc;
	t_command			*command;
	t_simple_command	*sc;
	t_simple_command	*cmd;
}				t_tmp;

void			print(t_list_cmd *l_command);
char 			*ft_ignoring(char *line);
void			back_slash(t_list_cmd *l_cmd);
void			variables(t_list_cmd *l_cmd, t_path *path);
int				count_antislach(char *line,int i);
char			*get_var_env1(t_path *path, char *var);
char			**ft_space_split(char const *s);
int				is_correct(char c);
void			*leak(char **spl, int j);
char			**ft_space_split(char const *s);
char			**ft_space_split_quote(char const *s);
t_list_cmd		*add_list_cmd(t_list_cmd *parent);
t_command		*add_command(t_command *parent, t_list_cmd *l_cmd);
t_command		*add_simple_cmd(t_command *parent, int i, t_list_cmd *l_cmd);
void			alloc_affect(t_list_cmd *l_cmd, char *command, int indice, t_save *save);
int				ft_check_line(char *line);
int				check_type_element(char *line, int *check_i_o, int count);
int				check_io_redirection(char *line, int *p);
void			check_element(t_list_cmd *l_cmd);
int				check_what_after(char c);
void			affect_redirection(t_list_cmd *l_cmd, char *line);
int				wich_redirection(int check);
int				check_redirection(char *line, int *i);
void			sort(t_list_cmd *l_cmd);
void			check_scommand(t_list_cmd *l_cmd);
char			*ignoring_quote(char *line);
void			quotes(t_list_cmd *l_cmd);
char			*ft_strjoin_command(t_simple_command *cmd);
void			parcs_simple_command(char *s_command, t_list_cmd *l_cmd);
void			parse_command(t_list_cmd *l_cmd, char *line);
void			parse_list_command(t_list_cmd *l_cmd, char *line);
void			free_tab(char ***tab);
void			ft_strdel(char **as);
void			free_element(t_elements **element);
void			free_s_command(t_simple_command **s_command);
void			free_scommand(t_simple_command **scommand);
void			free_command(t_command **command);
void			free_lcommand(t_list_cmd **l_command);
void			ft_exit(t_list_cmd *l_cmd, int error);
void			free_redirection(t_save **save);
void			init_simple_cmd(t_simple_command **parent, int i);
void			init_lcommand(t_list_cmd **parent);
void			loop_shell(t_path *path,t_list_cmd *cmd);
void			init(t_path *path, t_key *key, t_cmd *cmd);
void			show_env(char **path);
char			*search_env(char **env, char *str);
void			print_working_directory(t_path *path);
char			**ft_split_quotes(char const *s, char c);
char			**ft_space_split(char const *s);
char			*ft_str_in_str(const char *s1, const char *s2);
int				ft_2strlen(char **str);
char			*get_directory(t_path *path,char *cmd);
int				check_path(char *path, char *cmd);
void			getprogramme(t_path *path, t_command *cmd);
void			shift(int fd);
void			shift_extra(char *file, char *shifts, t_path *path,t_command *cmd);
char			*get_var_env(t_path *path, char *var);
void			cd_cmd(char *nextpath, t_path *path);
int				count_line(char **env);
int				export_cmd(char *name, t_path *path);
void			unset_cmd(char *name, t_path *path);
int				search_str(char *str1, char *str2, int l1, int l2);
char			*ft_str_to_equal(const char *s1, const char *s2, int len);
void			pipes_cmd(t_path *path, t_list_cmd *lst);
void			ft_sortstr(char **str);
char			**ft_strdup_extra(char **str);
int				cmdcheck(char *str);
int				cout_to_char(char *str, char c);
void			edit_env(char **env, char *var, char *res);
void			execute_foreign(t_list_cmd *lst, int piping);
int				lstsize(t_list_cmd *lst);
int				commande_effect(t_list_cmd *lst, t_path *path);
int				get_cmd(char *cmd, t_path *path, t_command *l_cmd);
int				get_cmd_(char *cmd, t_path *path, t_command *l_cmd);
void			free_lcommand(t_list_cmd **l_command);
void			bash_promp();
void			echo(char *line, t_path *patht);
void			commandes(char *cmd, t_path *path, t_command *l_cmd);
void			promp_bash(t_path *path, int ret, char **line);
void			show_export(char **env);
int				check_equal(char *str);
int				ft_strcmp(const char *s1, const char *s2);
char			*get_befor_equal(char *str);
int				check_paths(char *path);
char			**args(char *cmd,t_path *path);
char			*get_file(t_command *lcmd);
char			*get_file_shift(t_command *lcmd,char *shift);
int				double_red(char *file1, char *file2,char *shift);
int				create_file(char *file);
void			exit_exec(t_command *l_cmd);
long long		ft_atoi_long(char *str);
void			print_err_exite(char *s);
int				is_int(char *str);
int				count_digit(char *str);
int				size_args(t_command *l_cmd);
char			*get_shift(t_command *lcmd);
int				status_cmd_(int status,t_path *path);
void			frees(char **str);
void			bash_promp(void);
void			sort_execute(t_list_cmd *cmd, t_path *path);
int				manage_spaces(char *line);
int				set_new_cmd(char **lines, char *line, t_list_cmd *cmd, t_path *path);
void			signals(void);
void			manage_cntrc(char *line);
int				read_line(char **line);
void			exit_(char **line);
void			looping_exec(t_path *path, t_list_cmd *cmd, int *check);
void			init_(char **lines, int *check);
void			sigint_handler(int sig);
int				execute(t_path *path, t_command *cmd);
#endif
