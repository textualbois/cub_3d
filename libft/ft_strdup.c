/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:26:04 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 21:36:53 by isemin           ###   ########.fr       */
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
	res_str = (char *) malloc(size + 1);
	malloc_counter(__FILE__, __func__, __LINE__,1, PARSER, "ft_strdup malloc\n", res_str);
	if (res_str == NULL)
		return (NULL);
	while (i <= size)
	{
		res_str[i] = s[i];
		i++;
	}
	return (res_str);
}
