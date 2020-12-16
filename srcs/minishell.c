

#include "minishell.h"

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;

	init(&path,&key,&cmd);
	path.env->fullenv = env;
	loop_shell(&cmd,&path);
	return (0);
}