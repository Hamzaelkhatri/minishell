#include "minishell.h"

int check_space(char *str)
{
	int i = 0;

	while (str[++i] != '=')
		if (str[i] == ' ')
			return (0);
	if (str[i] != '=')
		return (0);
	i = 0;
	while (str[++i] != '=')
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

static char *get_after_equal(char *str)
{
	char *ptr;
	int i;

	if (!(ptr = malloc(sizeof(char) * ft_strlen(str))))
		return (NULL);
	ft_bzero(ptr, ft_strlen(str));
	i = 0;
	while (str[i])
	{
		ptr[i] = str[i];
		if (str[i] == ' ')
			break;
		i++;
	}
	return (ptr);
}

void sort_exp(char **env)
{
	char **ret;
	int i = 0;
	int k = 0;
	int l = 0;
	char *tmp;

	ret = malloc((count_line(env)) * sizeof(char *));
	l = count_line(env);
	while (i < l - 1)
	{
		ret[i] = env[i];
		i++;
	}
	i = 0;
	while (i < l-1)
	{
		k = i + 1;
		while (k < l-1)
		{
			if (ft_strcmp(ret[i],ret[k]) > 0)
			{
				tmp = ret[i];
				ret[i] = ret[k];
				ret[k] = tmp;
			}
			k++;
		}
		i++;
	}
	ret[i] = NULL;
	show_env(ret);
}

void export_cmd(char *name, char **env)
{
	int line = 0;
	if (!name)
		sort_exp(env);
	else if (!check_space(name))
	{
		ft_putstr_fd("bash$ : bad assignment", 1);
		return;
	}
	else
	{
		line = count_line(env);
		env[line] = get_after_equal(name);
		env[line + 1] = NULL;
	}
}
