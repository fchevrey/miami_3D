/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:45:23 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 14:45:51 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_map			***fill_map(t_parse parse, t_map **map, int nb_elem)
{
	t_map		***new;
	t_map		*tmp;
	int			y;
	int			x;

	y = 0;
	tmp = *map;
	if (!(new = (t_map ***)malloc(sizeof(t_map **) * (parse.nb_line + 2))))
		malloc_failed("ft_fill_tab");
	while (tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		x = 0;
		if (!(new[y] = (t_map **)malloc(sizeof(t_map *) * (nb_elem + 2))))
			malloc_failed("ft_fill_tab2");
		while (x <= parse.nb_elem_line)
		{
			new[y][x++] = tmp;
			tmp = tmp->next;
		}
		new[y++][x] = NULL;
	}
	new[y] = NULL;
	return (new);
}
