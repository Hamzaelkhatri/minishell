#include "minishell.h"

int check_space(char *str)
{
	int i = 0;
	while(str[++i] != '=')
		if(str[i] == ' ')
			return (0);
	if(str[i] != '=')
		return (0);
	i = 0;
	while(str[++i] != '=')
		if(!ft_isdigit(str[i]))
			return (1);
	return (0);
}

static char*  get_to_space(char *str)
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

char *get_befor_equal(char *str)
{
	char *ptr;
	int i;

	i = 0;
	if(!(ptr = malloc(sizeof(char) * cout_to_char(str,'='))))
		return (NULL);
	while(str[i] != '=')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}


char *get_after_equal(char *str)
{
	int i;

	i = ft_strlen(get_befor_equal(str));

	return(&str[i+1]);
}


void	export_cmd(char *name,char **env)
{
	int line = 0; 
	
	if(!check_space(name))
	{
		ft_putstr_fd("bash$ : bad assignment",1);
		return ;
	}
	if(!search_env(env,get_befor_equal(name)))
	{
		line = count_line(env);
		env[line] = get_to_space(name);
		env[line+1] = NULL;
	}
	else
		edit_env(env,get_befor_equal(name),get_after_equal(name));
}
