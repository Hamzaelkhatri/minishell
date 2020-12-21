#include "minishell.h"

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;

	init(&path,&key,&cmd);
	path.env->fullenv = env;

//	show_env(path.env->fullenv);

//	write(1,"----------------------------------\n",30);
///	ft_sortstr(env);
///	show_env(env);
	pipes_cmd("cat k","pwd",&path);
	//getprogramme(&path,"ls | less");
	return (0);
}
