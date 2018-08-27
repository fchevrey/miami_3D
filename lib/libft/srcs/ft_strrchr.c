/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:04:06 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/21 15:04:38 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strrchr(const char *s, int c)
{
	char	car;
	int		i;
	char	*result;

	i = -1;
	car = (char)c;
	result = NULL;
	while (s[++i] != '\0')
		if (s[i] == car)
			result = (char*)s + i;
	if (s[i] == car)
		result = (char*)s + i;
	return (result);
}
