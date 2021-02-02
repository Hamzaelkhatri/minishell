
#include "minishell.h"

void ft_exit(t_list_cmd *l_cmd, int error)
{
	ft_putendl_fd(strerror(error), 2);
	free_lcommand(&l_cmd);
	exit(1);
}

int check_int(char *str)
{
	int i;

	i = 0;
	str = ft_strtrim(str, "\n");
	str = ignoring_quote(str);
	while (str[i] && (str[i] < 33 || str[i] == '-' || str[i] == '+'))
		i++;
	if (ft_atoi_long(str) <= LLONG_MIN && str[i - 1] != '-')
	{
		print_err_exite(str);
		return (255);
	}
	if (ft_atoi_long(str) < LLONG_MIN)
	{
		print_err_exite(str);
		return (0);
	}
	else if (ft_atoi_long(str) > LLONG_MAX)
	{
		print_err_exite(str);
		return (255);
	}
	else if (ft_atoi_long(str) <= LONG_MIN && count_digit(&str[i]) == 19)
		return (0);
	else if (count_digit(&str[i]) == 19 && str[i - 1] == '-')
	{
		print_err_exite(str);
		return (255);
	}
	while (str[i])
	{
		if ((!ft_isdigit(str[i]) && str[i] != 32 && str[i] != '\t') || count_digit(&str[i]) > 19)
		{
			print_err_exite(str);
			return (255);
		}
		i++;
	}
	return (ft_atoi(str));
}

void exit_exec(t_command *l_cmd)
{
	if (size_args(l_cmd) > 1 && is_int(l_cmd->s_left->right->l_element->argument))
	{
		ft_putendl_fd("\e[1;31mminishell: exit: too many arguments", 2);
		exit(EXIT_FAILURE);
	}
	if (l_cmd->s_left->right && l_cmd->s_left->right->l_element->argument)
	{
		ft_putendl_fd("exit", 1);
		exit(check_int(l_cmd->s_left->right->l_element->argument));
	}
	else
	{
		ft_putendl_fd("exit", 1);
		exit(EXIT_SUCCESS);
	}
}