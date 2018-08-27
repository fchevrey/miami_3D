/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 14:08:52 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/21 18:59:46 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		result;

	i = -1;
	j = 0;
	if (needle[0] == '\0')
		return ((char*)haystack);
	while (haystack[++i])
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
	}
	return (0);
}
