/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 20:06:24 by fchevrey          #+#    #+#             */
/*   Updated: 2018/03/14 16:27:20 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

static int		full_swap(char **swap, int fd)
{
	char	str[BUFF_SIZE + 1];
	int		rd;

	rd = -2;
	ft_bzero(str, BUFF_SIZE);
	if (!(*swap))
		*swap = ft_strnew(0);
	while (!(ft_strchr(*swap, '\n')) && (rd = read(fd, str, BUFF_SIZE)) > 0)
	{
		str[rd] = '\0';
		*swap = ft_strjoinf(*swap, str);
	}
	return (rd);
}

int				get_next_line(const int fd, char **line)
{
	static char		str[BUFF_SIZE + 1];
	char			*swap;
	char			*srch;
	int				rd;

	if (fd < 0 || fd > OPEN_MAX || line == NULL)
		return (-1);
	swap = ft_strdup(str);
	rd = full_swap(&swap, fd);
	srch = (ft_strchr(swap, '\n'));
	ft_bzero(str, BUFF_SIZE);
	if (srch)
		ft_strcpy(str, srch + 1);
	*line = ft_strsubf(swap, 0, ft_strlen(swap) - ft_strlen(srch));
	if (srch == NULL && (rd == -1))
		return (-1);
	if ((ft_strlen(*line) == 0) && (rd == 0))
		return (0);
	return (1);
}
