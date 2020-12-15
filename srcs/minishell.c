#include "../includes/minishell.h"


int count_line(char **env)
{
	int i = 0;
	if (!env)
		return (0);
	while (env[i])
		i++;
	return (i);
}

void	export_cmd(char *name,char **env)
{
	int i = 0;
	int line = count_line(env);
	printf("{%d}",line);
	env[line] = name;
	env[line+1] = NULL;
}


int		search_str(char *str1, char *str2, int l1, int l2)
{
	int i;
	i = 0;

	if (l1 != l2 || l1 == 0 || l2 == 0)
		return (0);
	else if (ft_strncmp(str1,str2,l1) == 0)
		return (1);
	return (0);
}

void	unset_cmd(char *name, t_path *path)
{
	int i = 0;
	char **spl;
	int check = 0;
	while (path->env->fullenv[i])
	{
		spl = ft_split(path->env->fullenv[i], '=');
		if ((ft_strlen(spl[0]) == 1) && spl[0][0] == '_')
			break ;
		if (search_str(spl[0], name,ft_strlen(spl[0]), ft_strlen(name)) == 1)
		{
			// path->env->fullenv[i] = path->env->fullenv[i+1];
			check++;
		}
		if (check)
			path->env->fullenv[i] = path->env->fullenv[i+1];
		// {
		// 	path->env->fullenv[i] =  path->env->fullenv[count_line(path->env->fullenv)-1];
		// 	path->env->fullenv[count_line(path->env->fullenv)-1] = NULL;
		// }
		i++;
	}

	path->env->fullenv[i+1] = NULL;
	// path->env->fullenv[count_line(path->env->fullenv)-1] = NULL;
}

int main(int argc, char **argv,char **env)
{
	t_path path;
	t_key key;
	t_cmd cmd;
	// char *env_tmp[33];
	char *s;
	init(&path,&key,&cmd);
	path.env->fullenv = env;

	// export_cmd("myvar=300",path.env->fullenv);
	unset_cmd("_",&path);
	show_env(path.env->fullenv);
	// cd_cmd("srcs",&path);
	get_directory(&path);
	// loop_shell(&cmd,&path);
	// getprogramme(&path,"ls");
	//printf("hi");
	return (0);
}