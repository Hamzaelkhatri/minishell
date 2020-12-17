#include "minishell.h"

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;

	init(&path,&key,&cmd);
	path.env->fullenv = env;
	//pipes_cmd("ls","more",&path);
	// export_cmd("myvar=300",path.env->fullenv);
	// unset_cmd("_",&path);
	// show_env(path.env->fullenv);
	// cd_cmd("srcs",&path);
	// get_directory(&path);
	// loop_shell(&cmd,&path);
	getprogramme(&path,"ls | more");
	return (0);
}
