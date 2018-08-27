/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 17:34:30 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/26 19:51:21 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		calcul;

	j = 0;
	i = ft_strlen(dst);
	calcul = ft_strlen(src) + ft_strlen(dst);
	if (size <= ft_strlen(dst))
		return (size + ft_strlen(src));
	while ((src[j] != '\0') && i < (size - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (calcul);
}
