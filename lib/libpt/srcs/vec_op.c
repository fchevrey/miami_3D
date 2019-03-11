/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 19:49:08 by fchevrey          #+#    #+#             */
/*   Updated: 2019/03/11 18:25:11 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libpt.h"

static t_vec		ft_div_pt(t_vec crd1, char operand, t_vec crd2)
{
	t_vec		result;

	result = vec_set(0, 0, 0);
	if (crd2.x == 0 || crd2.y == 0 || crd2.z == 0)
		return (result);
	if (operand == '/')
	{
		result.x = crd1.x / crd2.x;
		result.y = crd1.y / crd2.y;
		result.z = crd1.z / crd2.z;
	}
	else if (operand == '%')
	{
		result.y = crd1.y % crd2.y;
		result.x = crd1.x % crd2.x;
		result.z = crd1.z % crd2.z;
	}
	return (result);
}

t_vec				vec_op(t_vec crd1, char operand, t_vec crd2)
{
	t_vec		result;

	result = vec_set(0, 0, 0);
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
	else if (operand == '/' || operand == '%')
		result = ft_div_pt(crd1, operand, crd2);
	return (result);
}
