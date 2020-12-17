

#include "minishell.h"

char **ft_strdouble(char **str)
{
	int i = 0;
	int j;
	char **ptr;
	ptr = malloc(count_line(str) + 100);
	while(str[i])
	{
		//ptr[i] = ft_strdup(str[i]);
		ptr[i] = malloc(ft_strlen(str[i]) + 1);
		j = 0;
		while(str[i][j])
		{
			ptr[i][j] = str[i][j];
			j++;
		}
		ptr[i][j] = '\0';
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;

	init(&path,&key,&cmd);
	path.env->fullenv = ft_strdouble(env);
	//	show_env(path.env->fullenv);
	//	printf("%s",get_var_env(&path,"$LESS"));
	
	//show_export(&path);
	printf("\n-------------------------------------------------\n");
	//export_cmd("hr=ls",path.env->fullenv);
	show_env(path.env->fullenv);
	printf("\n-------------------------------------------------\n");	
	show_env(env);
	return (0);
}
