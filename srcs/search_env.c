#include "minishell.h"

char    *ft_str_to_equal(const char *s1, const char *s2,int len)
{
        size_t i;
        size_t j;

        i = 0;
        j = 0;
        if (!s2[j])
                return ((char *)s1);
        while (s1[i] && i<len)
        {
                j = 0;
                if (s1[i] == s2[j])
                {
                        j = 1;
                        while (s2[j] && s2[j] == s1[i + j] && (i + j) < len)
                                j++;
                        if (!s2[j] && s1[i+j] == '=')
                                return ((char *)&s1[i]);
                }
                i++;
        }
        return (NULL);
}



int cout_to_equal(char *str)
{
	int i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

char *search_env(char **env,char *str)
{
    int i;
    int j;
    char *tmp;

    j = ft_strlen(str)+1;
    i = 0;
    while (env[i])
    {
        if (ft_str_to_equal(env[i],str,ft_strlen(str)))
        {
            tmp = ft_str_to_equal(env[i],str,cout_to_equal(str));
            return &tmp[j];
        }
        i++;
    }
    return (NULL);
}
