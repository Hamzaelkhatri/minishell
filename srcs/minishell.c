

#include "minishell.h"

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;

	init(&path,&key,&cmd);
	path.env->fullenv = env;
	return (0);
}
