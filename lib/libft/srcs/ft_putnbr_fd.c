/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:31:35 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/27 17:33:59 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_fd(int nbr, int fd)
{
	long			max;
	unsigned int	already_print;
	unsigned int	nb;
	char			to_print;

	max = 1;
	nb = (unsigned int)nbr;
	already_print = 0;
	if (nbr < 0)
		ft_putchar_fd('-', fd);
	if (nbr < 0)
		nb = (unsigned int)(-nbr);
	if (nbr == 0)
		ft_putchar_fd('0', fd);
	while (max <= nb)
		max = max * 10;
	max = max / 10;
	while (max > 0)
	{
		to_print = (nb - already_print) / max;
		already_print = already_print + to_print * max;
		ft_putchar_fd('0' + to_print, fd);
		max = max / 10;
	}
}
