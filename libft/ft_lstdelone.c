/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 20:48:32 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 21:35:40 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		if (lst->content != NULL)
			del(lst->content);
		malloc_counter(__FILE__, __func__, __LINE__,-1, PARSER, "lstdelone free\n", lst);
		free(lst);
		lst = NULL;
	}
}
