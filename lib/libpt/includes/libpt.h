/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libpt.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 18:05:06 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/09 12:10:01 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBPT_H
# define LIBPT_H
# include "libft.h"

typedef struct		s_point
{
	int		x;
	int		y;
}					t_point;

typedef struct		s_ptfl
{
	float	x;
	float	y;
}					t_ptfl;

typedef struct		s_ptdb
{
	double	x;
	double	y;
}					t_ptdb;

typedef struct		s_vec
{
	int		x;
	int		y;
	int		z;
}					t_vec;

typedef struct		s_vecfl
{
	float		x;
	float		y;
	float		z;
}					t_vecfl;

t_point				pt_bc(t_point crd, char operand, int nb);
t_point				pt_op(t_point crd1, char operand, t_point crd2);
t_point				pt_set(int x, int y);
void				pt_yplus(t_point *src, int ymin, int ymax);
void				pt_ypluseg(t_point *src, int ymin, int ymax);
void				ft_putcrd(t_point crd);
void				pt_swap(t_point *pt1, t_point *pt2);
t_ptfl				ptfl_op(t_ptfl crd1, char operand, t_ptfl crd2);
t_ptfl				ptfl_bc(t_ptfl crd, char operand, float nb);
t_ptfl				ptfl_set(float x, float y);
t_ptfl				ptfl_yplus(t_ptfl src, t_ptfl incr, float ymin,
		float ymax);
t_ptfl				ptfl_ypluseg(t_ptfl src, t_ptfl incr, float ymin,
		float ymax);
void				ptfl_swap(t_ptfl *pt1, t_ptfl *pt2);
t_ptdb				ptdb_op(t_ptdb crd1, char operand, t_ptdb crd2);
t_ptdb				ptdb_bc(t_ptdb crd, char operand, double nb);
t_ptdb				ptdb_set(double x, double y);
void				vec_swap(t_vec *pt1, t_vec *pt2);
t_vec				vec_bc(t_vec crd, char operand, int nb);
t_vec				vec_set(int x, int y, int z);
t_vec				vec_op(t_vec crd1, char operand, t_vec crd2);
void				vecfl_swap(t_vecfl *pt1, t_vecfl *pt2);
t_vec				vecfl_bc(t_vecfl crd, char operand, float nb);
t_vec				vecfl_set(float x, float y, float z);
t_vec				vecfl_op(t_vecfl crd1, char operand, t_vecfl crd2);

#endif
