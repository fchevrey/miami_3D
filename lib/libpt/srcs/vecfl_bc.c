/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecfl_bc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 12:30:03 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:25:31 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpt.h"

static t_vecfl		ft_div_vec(t_vecfl crd, char operand, float nb)
{
	t_vecfl		result;

	result = vecfl_set(0, 0, 0);
	if (nb == 0)
		return (result);
	if (operand == '/')
	{
		result.x = crd.x / nb;
		result.y = crd.y / nb;
		result.z = crd.z / nb;
	}
	return (result);
}

t_vecfl				vecfl_bc(t_vecfl crd, char operand, float nb)
{
	t_vecfl		result;

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
	else if (operand == '/')
		result = ft_div_vec(crd, operand, nb);
	return (result);
}
