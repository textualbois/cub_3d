/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmamoten <vmamoten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:26:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/23 19:08:01 by vmamoten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*res_str;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	i = 0;
	res_str = (char *)malloc(size + 1);
	if (res_str == NULL)
		return (NULL);
	while (i <= size)
	{
		res_str[i] = s[i];
		i++;
	}
	return (res_str);
}
