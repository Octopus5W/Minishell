/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:12:04 by thblonde          #+#    #+#             */
/*   Updated: 2024/10/18 17:52:35 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		len = 0;
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = ft_calloc((len + 1), sizeof(char));
	if (!new)
		return (NULL);
	ft_memcpy(new, s + start, len);
	new[len] = '\0';
	return (new);
}
