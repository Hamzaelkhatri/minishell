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

	ret = malloc((count_line(env) + 1) * sizeof(char *));
	l = count_line(env);
	while (i < l)
	{

		ret[i] = env[i];
		i++;
	}
	i = 0;
	while (i < l)
	{
		k = i + 1;
		while (k < l)
		{
			if (ft_strcmp(ret[i], ret[k]) > 0)
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
	show_env1(ret);
}

int *check_modif(char **env, char *name)
{
	int i = 0;
	int *tab;
	char **tmp1;
	char **tmp2;
	tab = malloc(sizeof(int) * 2);
	tab[0] = 0;
	tab[1] = 0;
	while (env[i])
	{
		tmp1 = ft_split(name, '=');
		tmp2 = ft_split(env[i], '=');
		if (!ft_strcmp(tmp1[0], tmp2[0]))
		{
			tab[1] = 1;
			tab[0] = i;
		}
		i++;
	}
	free(tmp1);
	free(tmp2);
	return (tab);
}

void export_cmd(char *name, char **env)
{
	int line = 0;
	int i = 0;
	int *tab;
	char **tmp;
	if (!name)
		sort_exp(env);
	else
	{
		name = ft_strtrim(name, "\n");
		tab = check_modif(env,name);
		line = count_line(env);
		if (name[ft_strlen(name)-1] == '=')
		{
			name = ft_strjoin(name,"''");
			env[line] = name;
			env[line + 1] = NULL;
		}
		else if (tab[1] == 0)
		{
			tmp = shell_space_split(name);
			i=0;
			while (i < count_line(tmp))
			{
				env[line++] = tmp[i++];
			}
			env[line] = NULL;
		}
		else
		{
			env[tab[0]] = name;
		}
	}
}
