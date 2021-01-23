#include "../includes/minishell.h"

void check_errors1(char *line,t_shell *sh) {
  int i;
  char **sp_free;

  i = 0;
  sp_free = shell_space_split(line);
  while (line[i] != '\0' && line[i + 1] != '\0') {
    if (check_revers_check(line[i], line[i + 1], '>', ';') == 1) {
      printf("Error : Syntax error \n");
      exit(1);
    }
    if (check_revers_check(line[i], line[i + 1], '>', '|') == 1) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if (check_revers_check(line[i], line[i + 1], '>', '<') == 1) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '>') {
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
  i = 0;
  while (sp_free[i] != (void *)0 && sp_free[i + 1] != (void *)0) {
    if ((strcmp(sp_free[i], ";") == 0 && strcmp(sp_free[i + 1], ">") == 0) ||
        (strcmp(sp_free[i], ">") == 0 && strcmp(sp_free[i + 1], ";") == 0)) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], ">") == 0) ||
        (ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], ">") == 0)) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
}

void check_errors2(char *line,t_shell *sh) {
  int i;
  char **sp_free;

  i = 0;
  sp_free = shell_space_split(line);
  while (line[i] != '\0' && line[i + 1] != '\0') {
    if (check_revers_check(line[i], line[i + 1], '<', ';') == 1) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if (check_revers_check(line[i], line[i + 1], '<', '|') == 1) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if (check_revers_check(line[i], line[i + 1], '<', '>') == 1) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if (line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>') {
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
  i = 0;
  while (sp_free[i] != (void *)0) {
    if ((ft_strcmp(sp_free[i], "|") == 0 &&
         ft_strcmp(sp_free[i + 1], "<") == 0) ||
        (ft_strcmp(sp_free[i], "<") == 0 &&
         ft_strcmp(sp_free[i + 1], "|") == 0)) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((ft_strcmp(sp_free[i], ";") == 0 &&
         ft_strcmp(sp_free[i + 1], "<") == 0) ||
        (ft_strcmp(sp_free[i], "<") == 0 &&
         ft_strcmp(sp_free[i + 1], ";") == 0)) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], "<") == 0) ||
        (ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], "<") == 0)) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
}

void check_errors3(char *line,t_shell *sh) {
  int i;
  char **sp_free;

  i = 0;
  sp_free = shell_space_split(line);

  while (line[i] != '\0') {
    if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '|') ||
        (line[i] == '|' && line[i + 1] == '>' && line[i + 2] == '>')) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((line[i] == '>' && line[i + 1] == '>' && line[i + 2] == ';') ||
        (line[i] == ';' && line[i + 1] == '>' && line[i + 2] == '>')) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>') ||
        (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '<')) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ((line[i] == '<' && line[i + 1] == '>' && line[i + 2] == '>') ||
        (line[i] == '>' && line[i + 1] == '>' && line[i + 2] == '<')) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
  i = 0;
  while (sp_free[i] != (void *)0) {
    if ((ft_strcmp(sp_free[i], "|") == 0 &&
         ft_strcmp(sp_free[i + 1], ">>") == 0) ||
        (ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], "|") == 0)) {
      printf("Error : Syntax error \n");
      exit(1);
    }
    if ((ft_strcmp(sp_free[i], ";") == 0 &&
         ft_strcmp(sp_free[i + 1], ">>") == 0) ||
        (ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], ";") == 0)) {
      printf("Error : Syntax error \n");
      exit(1);
    }
    if ((ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], ">>") == 0) ||
        (ft_strcmp(sp_free[i], ">>") == 0 &&
         ft_strcmp(sp_free[i + 1], ">>") == 0)) {
      printf("Error : Syntax error \n");
      exit(1);
    }
    i++;
  }
}

void check_seperator_errors(char *line,t_shell *sh) {
  int i;
  char **sp_free;

  i = 0;

  sp_free = shell_space_split(line);
  while (line[i] != '\0') {
    if ((line[i] == '|' && line[i + 1] == ';') ||
        (line[i] == ';' && line[i + 1] == '|')) {
      printf("Error : Syntax error\n");
      exit(1);
    }
    if ( (line[i] == '|' && line[i + 1] == '|') ||
        (line[i] == ';' && line[i + 1] == ';')) {
  // puts("here");
      printf("Error : Syntax error\n");
      exit(1);
    }
    i++;
  }
  i = 0;
  while (sp_free[i] != (void *)0) {
    if ((ft_strcmp(sp_free[i], "|") == 0 &&
         ft_strcmp(sp_free[i + 1], ";") == 0) ||
        (ft_strcmp(sp_free[i], ";") == 0 &&
         ft_strcmp(sp_free[i + 1], "|") == 0)) {
      printf("Error : Syntax error \n");
      exit(1);
    }
    if ((ft_strcmp(sp_free[i], "|") == 0 &&
         ft_strcmp(sp_free[i + 1], "|") == 0) ||
        (ft_strcmp(sp_free[i], ";") == 0 &&
         ft_strcmp(sp_free[i + 1], ";") == 0)) {
      printf("Error : Syntax error \n");
      exit(1);
    }
    i++;
  }
}

void first_check(char *line) {

  int i;

  i = 0;
  while (line[i]) {
    if (line[i] == '<' && line[i + 1] == '<')
      {
          printf("Error : Syntax error \n");
      exit(1);
  }
  i++;
  }
}
void check_line_error(char *line, t_shell *sh) {
    first_check(line);

  if (line[0] == '|')
  {
    write(1,"Syntax error near unexpected token Pipe",41);
    exit(1);
  }
  else if (line[0] == ';')
  {
    write(1,"Syntax error near unexpected token comma",41);
    exit(1);
  }
  else if ((line[0] == '\'' || line[0] == '\"') && ((line[1] == '<' || line[1]  == '>' ||
           (line[1]  == '>' && line[2] == '>') )))
           {
             write(1,"Command not found: >",21);
             exit(1);
  }

  else if (check_redirection(line) == 1 && check_quote1(line) == 0) {

    check_errors1(line,sh);
    check_errors2(line,sh);
    check_errors3(line,sh);

  } else  if (check_quote1(line) == 0)
    check_seperator_errors(line,sh);
}