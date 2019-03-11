/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_failed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 18:04:22 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:04:24 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void			malloc_failed(char *str)
{
	ft_putstr(str);
	ft_putendl(" : has failed");
	exit(EXIT_FAILURE);
}
