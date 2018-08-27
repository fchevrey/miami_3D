/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 20:23:11 by fchevrey          #+#    #+#             */
/*   Updated: 2018/01/16 12:09:28 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	car;
	int		i;

	if (s == NULL)
		return (NULL);
	i = -1;
	car = (char)c;
	while (s[++i] != '\0')
		if (s[i] == car)
			return ((char*)s + i);
	if (s[i] == car)
		return ((char*)s + i);
	return (NULL);
}
