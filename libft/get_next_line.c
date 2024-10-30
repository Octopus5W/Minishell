/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:14:17 by thblonde          #+#    #+#             */
/*   Updated: 2024/10/24 12:41:09 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_alloc(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

static char	*read_file(int fd, char *stash)
{
	char	*buf;
	int		char_read;

	char_read = 1;
	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	while (char_read && !(gnl_strchr(stash, '\n')))
	{
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read == -1)
			return (free_alloc(&buf), free_alloc(&stash), NULL);
		buf[char_read] = '\0';
		stash = gnl_strjoin(stash, buf);
		if (!stash)
			return (NULL);
	}
	free_alloc(&buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	int		i;
	char	*line;

	i = 0;
	if (stash[i] == '\0')
		return (NULL);
	while (stash[i] != '\n' && stash[i])
		i++;
	line = gnl_substr(stash, 0, i + 1);
	return (line);
}

static char	*clear_stash(char *stash)
{
	int		i;
	char	*tmp;

	i = 0;
	while (stash[i] != '\n' && stash[i])
		i++;
	if (stash[i] == '\0')
		return (free_alloc(&stash), NULL);
	tmp = gnl_substr(stash, i + 1, gnl_strlen(stash));
	free_alloc(&stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1 || BUFFER_SIZE >= 2147483647)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clear_stash(stash);
	return (line);
}
