
#include "../includes/minishell.h"
int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
  
	init(&path,&key,&cmd);
	path.env->fullenv = env;
// 	get_directory(&path);
	pipes_cmd("cat k","pwd",&path);
	return (0);
}
