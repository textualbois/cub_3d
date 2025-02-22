/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:04:29 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 21:35:17 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res_ptr;
	size_t	i;

	res_ptr = (char *) malloc(nmemb * size);
	malloc_counter(__FILE__, __func__, __LINE__,1, PARSER, "generic calloc\n", res_ptr);
	i = 0;
	if (res_ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		res_ptr[i] = 0;
		i++;
	}
	return ((void *) res_ptr);
}
