/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 15:42:53 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/28 16:00:32 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

static int			ft_is_whitespace(char c)
{
	if (c != '\t' && c != '\n' && c != ' ')
		return (0);
	return (1);
}

static size_t		ft_find_start(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_whitespace(str[i]) == 0)
			return (i);
		i++;
	}
	return (0);
}

static size_t		ft_find_end(const char *str)
{
	size_t	i;

	i = 0;
	i = ft_strlen(str);
	if (i == 0)
		return (0);
	while (str[--i])
		if (ft_is_whitespace(str[i]) == 0)
			return (i);
	return (0);
}

char				*ft_strtrim(char const *s)
{
	char	*dst;
	size_t	size;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s)
		return (NULL);
	start = ft_find_start(s);
	end = ft_find_end(s);
	size = 1 + end - start;
	if (end == 0 && start == 0 && ft_is_whitespace(s[0]) == 1)
		size = 0;
	dst = ft_strnew(size);
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (++i <= size)
		dst[i - 1] = s[(i - 1) + start];
	dst[i] = '\0';
	return (dst);
}
