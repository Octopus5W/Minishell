/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 18:06:39 by thblonde          #+#    #+#             */
/*   Updated: 2024/10/18 17:51:59 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len_word(char const *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s != c)
	{
		len++;
		s++;
	}
	return (len);
}

int	count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (*s != c)
		{
			words++;
			s += len_word(s, c);
		}
		else
			s++;
	}
	return (words);
}

void	*free_malloc(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**strs;
	int		i;
	int		words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	strs = malloc(sizeof(char *) * (words + 1));
	if (!strs)
		return (NULL);
	strs[words] = NULL;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			strs[i] = ft_substr(s, 0, len_word(s, c));
			if (!strs[i++])
				return (free_malloc(strs));
			s += len_word(s, c);
		}
		else
			s++;
	}
	return (strs);
}
