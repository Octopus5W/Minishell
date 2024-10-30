/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thomas <thomas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 08:31:20 by thblonde          #+#    #+#             */
/*   Updated: 2024/10/18 17:52:07 by thomas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;

	str = malloc((ft_strlen(s1) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, ft_strlen(s1));
	str[ft_strlen(s1)] = '\0';
	return (str);
}
