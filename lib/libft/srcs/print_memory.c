/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 14:35:05 by fchevrey          #+#    #+#             */
/*   Updated: 2018/04/11 14:35:07 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_addr_base(unsigned char value)
{
	unsigned char	nbr;
	size_t			size;
	char			base[17];
	char			dst[3];
	int				i;

	i = -1;
	while (++i < 10)
		base[i] = '0' + i;
	i--;
	while (++i < 16)
		base[i] = 'a' + (i - 10);
	base[i] = '\0';
	size = 2;
	nbr = value;
	dst[size] = '\0';
	while (nbr)
	{
		dst[--size] = base[nbr % 16];
		nbr /= 16;
	}
	while (size != 0)
		dst[--size] = '0';
	ft_putstr(dst);
}

static void		display(int *i, char hexa[17])
{
	while (*i % 16 != 0)
	{
		ft_putchar(' ');
		ft_putchar(' ');
		if (*i % 2 == 0)
			ft_putchar(' ');
		*i = *i + 1;
	}
	ft_putstr(hexa);
	while (*i)
		hexa[--*i] = '\0';
	ft_putchar('\n');
}

void			print_memory(const void *addr, size_t size)
{
	unsigned char	byt;
	int				i;
	unsigned char	*ptr;
	char			hexa[17];

	ptr = (unsigned char*)addr;
	i = 17;
	while (i)
		hexa[--i] = '\0';
	i = 1;
	while (size)
	{
		byt = *ptr;
		hexa[i - 1] = '.';
		if (byt > 33 && byt < 126)
			hexa[i - 1] = (char)byt;
		ft_addr_base(byt);
		if (i % 2 == 0)
			ft_putchar(' ');
		if (i % 16 == 0 || size == 1)
			display(&i, hexa);
		i++;
		ptr++;
		size--;
	}
}
