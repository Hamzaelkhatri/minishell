
#include "minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	
	init(&path,&key);
	path.env = env;
	loop_shell(&key);
	return (0);
}
