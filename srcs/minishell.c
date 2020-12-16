
#include "minishell.h"

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;

	init(&path,&key,&cmd);
	path.env->fullenv = env;
	loop_shell(&cmd,&path);
	// char *env_tmp[33];
	char *s;
	init(&path,&key,&cmd);
	path.env->fullenv = env;
	// export_cmd("myvar=300",path.env->fullenv);
	unset_cmd("TMPDIR",&path);
	show_env(path.env->fullenv);
	// cd_cmd("srcs",&path);
	get_directory(&path);
	// loop_shell(&cmd,&path);
	// getprogramme(&path,"ls");
	return (0);
}