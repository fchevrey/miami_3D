/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecfl_op.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 12:28:40 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:26:00 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpt.h"

static t_vecfl		ft_div_pt(t_vecfl crd1, char operand, t_vecfl crd2)
{
	t_vecfl		result;

	result = vecfl_set(0, 0, 0);
	if (crd2.x == 0 || crd2.y == 0 || crd2.z == 0)
		return (result);
	if (operand == '/')
	{
		result.x = crd1.x / crd2.x;
		result.y = crd1.y / crd2.y;
		result.z = crd1.z / crd2.z;
	}
	return (result);
}

t_vecfl				vecfl_op(t_vecfl crd1, char operand, t_vecfl crd2)
{
	t_vecfl		result;

	result = vecfl_set(0, 0, 0);
	if (operand == '-')
	{
		result.x = crd1.x - crd2.x;
		result.y = crd1.y - crd2.y;
		result.z = crd1.z - crd2.z;
	}
	else if (operand == '+')
	{
		result.x = crd1.x + crd2.x;
		result.y = crd1.y + crd2.y;
		result.z = crd1.z + crd2.z;
	}
	else if (operand == '*')
	{
		result.x = crd1.x * crd2.x;
		result.y = crd1.y * crd2.y;
		result.z = crd1.z * crd2.z;
	}
	else if (operand == '/')
		result = ft_div_pt(crd1, operand, crd2);
	return (result);
}
