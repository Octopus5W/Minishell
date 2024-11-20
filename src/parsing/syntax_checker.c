// first check
int	quote_is_closed(const char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (!s[i])
				return (0);
		}
		if (s[i] == '\"')
		{
			i++;
			while (s[i] && s[i] != '\"')
				i++;
			if (!s[i])
				return (0);
		}
	}
	return (1);
}