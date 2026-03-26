/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 18:28:54 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/15 18:30:04 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_dprintf(int fd, const char *fmt, ...)
{
	va_list		ap;
	t_format	*f;
	size_t		result;

	if (!fmt || fd < 0 || fd > 1024)
		return (-1);
	result = 0;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			fmt++;
			f = ft_t_format_init(fd);
			if (!f || parse_format_specifier(&fmt, f) == -1)
				return (-1);
			result += convert_specifier(&ap, f);
			continue ;
		}
		if (write(fd, fmt++, 1) == -1)
			return (-1);
		result++;
	}
	va_end(ap);
	return ((int)result);
}
