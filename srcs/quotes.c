void	ignoring_quote_ext(char *line, int *i, int *index)
{
	char	wich;

	wich = (line[*i] == 34) ? 34 : 39;
	(*i)++;
	while (((line[*i] == '\\' && line[*i + 1] == wich) ||\
				line[*i] != wich) && line[*i])
	{
		if (line[*i] == '\\' && line[*i + 1] == wich)
			(*i)++;
		line[(*index)++] = line[(*i)++];
	}
	if (line[*i] == '\0')
		line[(*index)] = '\0';
	else
		(*i)++;
}

char	*ignoring_quote(char *line)
{
	int		i;
	int		index;
	char	wich;

	i = 0;
	index = 0;
	while (line[i])
	{
		while ((line[i] == '\\' && (line[i + 1] == 34 || line[i + 1] == 39))\
				|| (line[i] != 34 && line[i] != 39 && line[i]))
		{
			if (line[i] == '\\' && (line[i + 1] == 34 || line[i + 1] == 39))
				i++;
			line[index++] = line[i++];
		}
		if ((line[i] == 34 || line[i] == 39) && line[i])
			ignoring_quote_ext(line, &i, &index);
		if (line[i] == '\0')
			line[index] = '\0';
	}
	return (line);
}
