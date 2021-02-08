#include "minishell.h"

char *get_befor_equal(char *str)
{
	char *ptr;
	int i;

	i = 0;
	if (!(ptr = malloc(sizeof(char) * (cout_to_char(str, '=') + 1))))
		return (NULL);
	while (str[i] != '=' && str[i])
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
	char *tmp;

	tmp = get_befor_equal(str);
	if (!check_equal(str))
	{
		frees(&tmp);
		return (NULL);
	}
	i = ft_strlen(tmp);
	frees(&tmp);
	return (&str[i + 1]);
}

void show_export(char **env)
{
	int i;
	char *tmp;

	if (!env)
		return;
	i = 0;
	while (env[i])
	{
		tmp = get_befor_equal(env[i]);
		if (ft_strncmp("_", tmp, ft_strlen(env[i])))
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(tmp, 1);
			if (get_after_equal(env[i]))
			{
				ft_putstr_fd("=\"", 1);
				ft_putstr_fd(get_after_equal(env[i]), 1);
				ft_putstr_fd("\"", 1);
			}
			ft_putstr_fd("\n", 1);
		}
		frees(&tmp);
		i++;
	}
}

int check_space(char *str)
{
	int i = 0;

	while (str[i] != '=' && str[i])
	{
		if (str[i] == ' ')
			return (0);
		i++;
	}
	i = 0;
	while (str[++i] != '=')
		if (!ft_isdigit(str[i]))
			return (1);
	return (0);
}

static char *get_to_space(char *str)
{
	char *ptr;
	int i;

	i = 0;
	if (!(ptr = malloc(sizeof(char) * ft_strlen(str))))
		return (NULL);
	ft_bzero(ptr, ft_strlen(str));
	while (str[i])
	{
		ptr[i] = str[i];
		if (str[i] == ' ')
			break;
		i++;
	}
	return (ptr);
}

int check_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int get_extern_value(char *str)
{
	int i;

	i = 0;
	if (str[0] == '=' || !str[0] || ft_isdigit(str[0]))
		return (0);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int export_cmd(char *name, t_path *path)
{
	int line = 0;
	char *tmp;
	char *tmp1;

	name = ft_strtrim(name, "\n");
	tmp = get_befor_equal(name);
	if (!get_extern_value(tmp))
	{
		ft_putstr_fd("\e[1;31mexport :\e[1;31m", 2);
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(" bad assignment\n", 2);
		path->dollar = 127;
	}
	else
	{
		if (!check_equal(name))
		{
			tmp1 = name;
			name = ft_strjoin(name, "");
			frees(&tmp1);
		}
		if (!search_env(path->env->fullenv, tmp))
		{
			line = count_line(path->env->fullenv);
			path->env->fullenv[line] = name;
			path->env->fullenv[line + 1] = NULL;
		}
		else if (check_equal(name))
			edit_env(path->env->fullenv, tmp, get_after_equal(name));
		path->dollar = 0;
	}
	frees(&tmp);
	frees(&name);
	return (1);
}
