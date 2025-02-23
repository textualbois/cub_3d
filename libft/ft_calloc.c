/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:04:29 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 19:00:01 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*res_ptr;
	size_t	i;

	res_ptr = (char *)malloc(nmemb * size);
	i = 0;
	if (res_ptr == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		res_ptr[i] = 0;
		i++;
	}
	return ((void *)res_ptr);
}
