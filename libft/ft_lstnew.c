/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 18:39:59 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 21:36:03 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_list_head;

	new_list_head = (t_list *)malloc(sizeof(t_list));
	malloc_counter(__FILE__, __func__, __LINE__,1, PARSER, "list head malloc\n", new_list_head);
	if (new_list_head == NULL)
		return (NULL);
	new_list_head->content = content;
	new_list_head->next = NULL;
	return (new_list_head);
}
