/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:14:20 by thblonde          #+#    #+#             */
/*   Updated: 2024/10/24 12:42:42 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return (s);
}

char	*gnl_strcpy(char *dst, char *src)
{
	int	i;

	i = 0;
	if (!src)
		return (NULL);
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*joined;

	if (!s2)
		return (free_alloc(&s1), NULL);
	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		if (!s1)
			return (free_alloc(&s2), NULL);
		s1[0] = '\0';
	}
	joined = malloc(gnl_strlen(s1) + gnl_strlen(s2) + 1);
	if (!joined)
		return (free_alloc(&s1), free_alloc(&s2), NULL);
	gnl_strcpy(joined, s1);
	gnl_strcpy(joined + gnl_strlen(s1), s2);
	free_alloc(&s1);
	return (joined);
}

char	*gnl_substr(char *s, unsigned int start, int len)
{
	char	*p;
	int		i;

	if (!s)
		return (NULL);
	if (len > gnl_strlen(&s[start]))
		p = malloc((gnl_strlen(&s[start]) + 1) * sizeof(char));
	else
		p = malloc((len + 1) * sizeof(char));
	if (!p)
		return (NULL);
	if ((int)start >= gnl_strlen(s))
		start = gnl_strlen(s);
	i = 0;
	while (i < len && s[start + i])
	{
		p[i] = s[start + i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
