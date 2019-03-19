/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 14:45:09 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/13 17:51:09 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void			ft_add(int x, int y, int content, t_map **map)
{
	t_map *new;

	if (!(new = (t_map *)malloc(sizeof(t_map))))
		malloc_failed("ft_add");
	new->next = NULL;
	new->x = x;
	new->y = y;
	new->content = content;
	if (!*map)
	{
		new->prev = NULL;
		*map = new;
	}
	else
	{
		while ((*map)->next)
			*map = (*map)->next;
		(*map)->next = new;
		(*map)->next->prev = *map;
		(*map)->next->next = NULL;
	}
}

static int		check_first_line(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != ' ')
			return (-1);
		i++;
	}
	return (1);
}

int				ft_lin_is_good(char *str)
{
	int			i;
	static int	is_first = 0;

	i = 0;
	if (is_first == 0)
		if (check_first_line(str) < 0)
			return (0);
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && (str[i] != ' ')
		&& (str[i + 1] && str[i] != '-' && ((str[i] < '0' || str[i] > '9'))))
			return (0);
		if (str[i] == ' ' && str[i + 1] == ' ')
			return (0);
		if (str[i] == ' ' && str[i + 1] == '\0')
			return (0);
		i++;
	}
	is_first++;
	return (1);
}
