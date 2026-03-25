/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:36:06 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 14:50:06 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

long	ft_size_n_long(long n)
{
	long	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa_long(long n)
{
	char	*num;
	long	len;

	len = ft_size_n_long(n);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	while (len--)
	{
		if (n % 10 < 0)
			num[len] = -(n % 10) + '0';
		else
			num[len] = (n % 10) + '0';
		n /= 10;
	}
	return (num);
}

long	ft_size_n_utoa_base(unsigned long n, int len_base)
{
	unsigned long	len;

	len = 1;
	while (n >= (unsigned int)len_base)
	{
		n /= len_base;
		len++;
	}
	return (len);
}

char	*ft_utoa_base(unsigned long n, char *base)
{
	char			*num;
	unsigned long	len;
	int				len_base;

	len_base = ft_strlen(base);
	len = ft_size_n_utoa_base(n, len_base);
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	while (len--)
	{
		num[len] = base[n % len_base];
		n /= len_base;
	}
	return (num);
}
