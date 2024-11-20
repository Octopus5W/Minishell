char **parse_token(t_token tokens)
{
	char **args;
	int i;
	t_token *ptr;

	i = 0;
	ptr = &tokens;
	while (ptr)
	{
		i++;
		ptr = ptr->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	ptr = &tokens;
	while (ptr)
	{
		args[i] = ptr->value;
		i++;
		ptr = ptr->next;
	}
	args[i] = NULL;
	return (args);
}