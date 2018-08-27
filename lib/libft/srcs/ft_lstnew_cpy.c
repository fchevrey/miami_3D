/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_cpy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fchevrey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 17:03:03 by fchevrey          #+#    #+#             */
/*   Updated: 2018/08/17 16:08:46 by fchevrey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

t_list	*ft_lstnew_cpy(void const *content, size_t content_size, int id)
{
	t_list	*list;

	if (!(list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		list->content = NULL;
		list->id = 0;
	}
	else
	{
		if (!(list->content = (void*)malloc(content_size)))
			return (NULL);
		ft_memcpy(list->content, content, content_size);
		list->id = id;
	}
	list->next = NULL;
	return (list);
}
