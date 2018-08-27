/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:09:21 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/28 12:28:28 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t					i;
	const unsigned char		*cpy_src;
	unsigned char			*cpy_dst;
	unsigned char			car;
	unsigned char			car_stop;

	i = 0;
	cpy_src = src;
	cpy_dst = dst;
	car_stop = (unsigned char)c;
	while (i < n)
	{
		car = (unsigned char)cpy_src[i];
		cpy_dst[i] = car;
		i++;
		if (car == car_stop)
			return (dst + i);
	}
	return (0);
}
