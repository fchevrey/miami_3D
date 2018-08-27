/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 14:15:15 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/17 16:07:31 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t					i;
	const unsigned char		*cpy_src;
	unsigned char			*cpy_dst;
	unsigned char			*temp;
	unsigned char			car;

	i = 0;
	cpy_src = src;
	cpy_dst = dst;
	if (!(temp = (unsigned char*)malloc(sizeof(unsigned char) * n)))
		return (NULL);
	while (i < n)
	{
		temp[i] = (unsigned char)cpy_src[i];
		i++;
	}
	i = 0;
	while (i < n)
	{
		car = (unsigned char)temp[i];
		cpy_dst[i] = car;
		i++;
	}
	free(temp);
	return (dst);
}
