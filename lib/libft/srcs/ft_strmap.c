/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:31:06 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/28 16:01:45 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*dst;

	i = -1;
	if (!s || !f)
		return (NULL);
	dst = ft_strnew(ft_strlen(s));
	if (dst == NULL)
		return (NULL);
	while (s[++i])
		dst[i] = f(s[i]);
	return (dst);
}
