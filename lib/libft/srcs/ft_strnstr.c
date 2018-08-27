/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 21:08:32 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/21 19:00:32 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	int			j;
	int			result;

	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[i] && i < len)
	{
		if (haystack[i] != needle[j])
		{
			if (j > 0)
				i = result + 1;
			j = 0;
		}
		else
			j++;
		if (j == 1)
			result = i;
		if (needle[j] == '\0')
			return ((char*)haystack + result);
		i++;
	}
	return (0);
}
