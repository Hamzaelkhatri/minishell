/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaddad <ahaddad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:30:13 by zdnaya            #+#    #+#             */
/*   Updated: 2020/12/25 15:15:50 by ahaddad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sh_initial(t_list_cmd *lst, t_shell *sh)
{
  sh = malloc(sizeof(t_shell));
  sh->pipe = 0;
  sh->comma = 0;
  sh->count_pipe = 0;

  sh->count_comma = 0;
  lst->pipe = NULL;
  ft_bzero(lst, sizeof(t_list_cmd));
}

void check_line_error(char *line)
{
  int i;
  char **sp_free;

  i = 0;
  sp_free = ft_space_split(line);
  //        while ( sp_free[i])
  // {
  //     printf("==>%s\n",sp_free[i]);
  //     i++;
  // }
  while (line[i] != '\0')
  {
    // printf("==>%s\n",line);
    if ((line[i] == '|' && line[i + 1] == ';') ||
        (line[i] == ';' && line[i + 1] == '|'))
    {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((line[i] == '|' && line[i + 1] == '|') ||
        (line[i] == ';' && line[i + 1] == ';'))
    {
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
  i = 0;
  while (sp_free[i] != (void *)0)
  {
    if ((ft_strcmp(sp_free[i], "|") == 0 &&
         ft_strcmp(sp_free[i + 1], ";") == 0) ||
        (ft_strcmp(sp_free[i], ";") == 0 &&
         ft_strcmp(sp_free[i + 1], "|") == 0))
    {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((ft_strcmp(sp_free[i], "|") == 0 &&
         ft_strcmp(sp_free[i + 1], "|") == 0) ||
        (ft_strcmp(sp_free[i], ";") == 0 &&
         ft_strcmp(sp_free[i + 1], ";") == 0))
    {
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
}

int main(int argc, char **argv, char **env)
{
  t_read rd;
  t_shell sh;
  t_list_cmd lst;
  t_path path;
  t_key key;
  t_cmd cmd;
  int i;

  i = 0;
  (void)argc;
  rd.fd = open("cmd.txt", O_RDONLY);
  rd.line = malloc(sizeof(char) * BUFFER_SIZE);
  read(rd.fd, rd.line, BUFFER_SIZE);
  check_line_error(rd.line);
  sh_initial(&lst, &sh);
  init(&path, &key, &cmd);
  lst = *handle_line(&sh, &rd, &lst, env);
  /*check builtins command*/
  if (sh.comma == 1 && sh.pipe == 1)
    check_built_p(&sh, &lst, &cmd);
  else
    {
      check_built(&sh, &lst, &cmd);
    }
  /*end pars , begin execution*/
  path.env->fullenv = env;
  if (sh.comma == 1 && sh.pipe == 1)
    pipes_cmd("ls", "cat", &path, &lst);
  else
    pipes_cmd1("ls", "cat", &path, &lst);
  // export_cmd("myvar=300",path.env->fullenv);
  // unset_cmd("_",&path);
  // show_env(path.env->fullenv);
  // cd_cmd("srcs",&path);
  get_directory(&path);
  // loop_shell(&cmd,&path);
  // getprogramme(&path,"ls | more");
}