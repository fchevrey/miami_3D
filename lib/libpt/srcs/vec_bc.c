/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_bc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 19:48:30 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:25:46 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpt.h"

static t_vec		ft_div_vec(t_vec crd, char operand, int nb)
{
	t_vec		result;

	result = vec_set(0, 0, 0);
	if (nb == 0)
		return (result);
	if (operand == '/')
	{
		result.x = crd.x / nb;
		result.y = crd.y / nb;
		result.z = crd.z / nb;
	}
	else if (operand == '%')
	{
		result.y = crd.y % nb;
		result.x = crd.x % nb;
		result.z = crd.z % nb;
	}
	return (result);
}

t_vec				vec_bc(t_vec crd, char operand, int nb)
{
	t_vec		result;

	result = crd;
	if (operand == '-')
	{
		result.x = crd.x - nb;
		result.y = crd.y - nb;
		result.z = crd.z - nb;
	}
	else if (operand == '+')
	{
		result.x = crd.x + nb;
		result.y = crd.y + nb;
		result.z = crd.z + nb;
	}
	else if (operand == '*')
	{
		result.x = crd.x * nb;
		result.y = crd.y * nb;
		result.z = crd.z * nb;
	}
	else if (operand == '/' || operand == '%')
		result = ft_div_vec(crd, operand, nb);
	return (result);
}
