
#include "../includes/minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	char *s;
	
	init(&path,&key,&cmd);
	path.env->fullenv = env;
	cd_cmd("/goinfre/djejd",&path);
	get_directory(&path);
	loop_shell(&cmd,&path);
	getprogramme(&path,"pwd");
	return (0);
}