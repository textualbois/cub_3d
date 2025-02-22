/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isemin <isemin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:17:45 by isemin            #+#    #+#             */
/*   Updated: 2025/02/22 21:35:24 by isemin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	int_len(int n)
{
	size_t	size;

	size = (n <= 0);
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	pos;

	pos = int_len(n);
	res = (char *) malloc(pos + 1);
	malloc_counter(__FILE__, __func__, __LINE__,1, PARSER, "generic itoa malloc\n", res);
	if (res == NULL)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(res, (const char *)"-2147483648", pos + 1);
	else if (n == 0)
		ft_strlcpy(res, (const char *)"0", pos + 1);
	else
	{
		n = n - (2 * n * (n < 0));
		res[0] = '-';
		res[pos--] = '\0';
		while (n != 0)
		{
			res[pos--] = (n % 10) + 48;
			n /= 10;
		}
	}
	return (res);
}
