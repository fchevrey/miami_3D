/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_last.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 13:33:42 by fchevrey          #+#    #+#             */
/*   Updated: 2018/03/06 13:42:05 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstadd_last(t_list *alst, t_list *new_elem)
{
	t_list		*lst;

	if (alst == NULL || new_elem == NULL)
		return ;
	lst = alst;
	while (lst->next)
		lst = lst->next;
	lst->next = new_elem;
}
