/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 17:22:44 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/17 14:57:31 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

static size_t	ft_nb_words(char const *s, char c)
{
	size_t		i;
	size_t		words;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			words = words + 1;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (words);
}

static size_t	ft_len_word(char const *s, char c, int word)
{
	size_t		len;
	int			i;
	int			act_word;

	i = 0;
	len = 0;
	act_word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			act_word++;
		while (s[i] != '\0' && s[i] != c)
		{
			if (act_word == word)
				len++;
			i++;
		}
	}
	return (len);
}

static void		ft_full_dst(char const *s, char c, char **dst)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			j++;
			k = 0;
		}
		while (s[i] != '\0' && s[i] != c)
		{
			dst[j][k] = s[i];
			k++;
			i++;
		}
		dst[j][k] = '\0';
	}
}

char			**ft_strsplit(char const *s, char c)
{
	size_t		words;
	size_t		i;
	char		**dst;

	i = 0;
	if (!s)
		return (NULL);
	words = ft_nb_words(s, c);
	if (!(dst = (char**)malloc(sizeof(char *) * (words + 1))))
		return (NULL);
	while (++i <= words)
	{
		if (!(dst[i - 1] = ft_strnew(ft_len_word(s, c, i))))
			return (NULL);
	}
	if (words > 0)
		ft_full_dst(s, c, dst);
	dst[words] = NULL;
	return (dst);
}
