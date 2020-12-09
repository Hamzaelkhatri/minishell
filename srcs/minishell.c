#include "minishell.h"

int		main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	
	init(&path,&key,&cmd);
	path.env = env;
	get_directory(&path);
	getprogramme(&path,&cmd);
	// loop_shell(&cmd,&path)
	return (0);
}