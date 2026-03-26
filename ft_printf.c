/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 14:59:24 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 17:50:23 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_printf(const char *fmt, ...)
{
	va_list		ap;
	t_format	*f;
	size_t		result;

	if (!fmt)
		return (-1);
	result = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			f = ft_t_format_init(1);
			if (!f || parse_format_specifier(&fmt, f) == -1)
				return (-1);
			result += convert_specifier(&ap, f);
			continue ;
		}
		if (write(1, fmt++, 1) == -1)
			return (-1);
		result++;
	}
	va_end(ap);
	return ((int)result);
}
