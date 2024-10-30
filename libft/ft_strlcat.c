/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:01:46 by thblonde          #+#    #+#             */
/*   Updated: 2024/10/18 17:52:13 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	if (size <= dest_len)
		return (size + ft_strlen(src));
	ft_strlcpy(dest + dest_len, src, size - dest_len);
	return (dest_len + ft_strlen(src));
}
