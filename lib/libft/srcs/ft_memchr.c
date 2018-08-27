/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/16 17:08:34 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/21 17:18:19 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t					i;
	const unsigned char		*dest;
	unsigned char			car;

	dest = s;
	car = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		if (dest[i] == car)
			return ((void*)s + i);
		i++;
	}
	return (0);
}
