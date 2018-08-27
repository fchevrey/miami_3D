/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:13:14 by fchevrey          #+#    #+#             */
/*   Updated: 2018/01/11 20:26:47 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strsubf(char *c, unsigned int start, size_t len)
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
	ft_strdel(&c);
	return (dest);
}
