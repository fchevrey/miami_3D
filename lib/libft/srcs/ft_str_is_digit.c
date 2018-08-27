/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 19:00:38 by fchevrey          #+#    #+#             */
/*   Updated: 2018/02/26 17:53:55 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_digit(const char *src)
{
	int		i;

	if (!src)
		return (-1);
	i = -1;
	while (src[++i])
	{
		if (src[i] == '-' && (src[i + 1] < '0' || src[i + 1] > '9'))
			return (0);
		else if (src[i] != '-' && (src[i] < '0' || src[i] > '9'))
			return (0);
	}
	if (i == 0)
		return (0);
	return (1);
}
