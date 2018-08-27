/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:04:59 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/28 15:06:46 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strsub(char const *c, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*dest;

	if (!c)
		return (NULL);
	if (!(dest = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = c[i + start];
		i++;
	}
	return (dest);
}
