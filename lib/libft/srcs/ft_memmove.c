/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:30:40 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/22 16:40:15 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t					i;
	const unsigned char		*cpy_src;
	unsigned char			*cpy_dst;

	cpy_src = src;
	cpy_dst = dst;
	if (dst == src || len == 0)
		return (dst);
	if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			cpy_dst[i] = (unsigned char)cpy_src[i];
			i++;
		}
		return (dst);
	}
	i = len;
	while (--i)
		cpy_dst[i] = cpy_src[i];
	cpy_dst[i] = cpy_src[i];
	return (dst);
}
