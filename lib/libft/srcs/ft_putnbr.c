/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_numbers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:11:57 by fchevrey          #+#    #+#             */
/*   Updated: 2017/11/26 19:50:18 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr(int nbr)
{
	long			max;
	unsigned int	already_print;
	unsigned int	nb;
	char			to_print;

	max = 1;
	nb = (unsigned int)nbr;
	already_print = 0;
	if (nbr < 0)
		ft_putchar('-');
	if (nbr < 0)
		nb = (unsigned int)(-nbr);
	if (nbr == 0)
		ft_putchar('0');
	while (max <= nb)
		max = max * 10;
	max = max / 10;
	while (max > 0)
	{
		to_print = (nb - already_print) / max;
		already_print = already_print + to_print * max;
		ft_putchar('0' + to_print);
		max = max / 10;
	}
}
