#include "minishell.h"

int check_space(char *str)
{
	int i = 0;
	while(str[++i] != '=')
		if(str[i] == ' ')
			return (0);
	//if(str[i] != '=')
	//	return (0);
	i = 0;
	while(str[++i] != '=')
		if(!ft_isdigit(str[i]))
			return (1);
	return (0);
}

static char*  get_after_equal(char *str)
{
	char *ptr;
	int i;
       	
	if(!(ptr = malloc(sizeof(char) * ft_strlen(str))))
		return (NULL);
	ft_bzero(ptr,ft_strlen(str));
	i = 0;
	while(str[i])
	{
		ptr[i] = str[i];
		if(str[i] == ' ')
			break;
		i++;
	}
	return (ptr);
}

void	export_cmd(char *name,char **env)
{
	int line = 0; 
	
	if(!check_space(name))
	{
		ft_putstr_fd("bash$ : bad assignment",1);
		return ;
	}
	line = count_line(env);
	env[line] = get_after_equal(name);
	env[line + 1]= NULL;
}
