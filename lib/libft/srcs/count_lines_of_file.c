/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 19:42:22 by fchevrey          #+#    #+#             */
/*   Updated: 2018/02/13 20:46:20 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int		count_lines_of_file(char *filename)
{
	char	*line;
	int		nb_line;
	int		fd;
	int		gnl;

	line = NULL;
	nb_line = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 2)
		return (-1);
	while ((gnl = get_next_line(fd, &line)) > 0)
	{
		nb_line++;
		ft_strdel(&line);
	}
	ft_strdel(&line);
	if (gnl == -1)
		return (-1);
	close(fd);
	return (nb_line);
}
