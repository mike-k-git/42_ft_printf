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

ssize_t	convert_specifier(va_list *ap, t_format *f)
{
	ssize_t	written;

	if (f->specifier == '%')
		written = process_percent();
	else if (f->specifier == 'c')
		written = process_char(f, va_arg(*ap, int));
	else if (f->specifier == 's')
		written = process_string(f, va_arg(*ap, char *));
	else if (f->specifier == 'd' || f->specifier == 'i')
		written = process_int(f, va_arg(*ap, int));
	else if (f->specifier == 'u')
		written = process_uint(f, va_arg(*ap, unsigned int));
	else if (f->specifier == 'p')
		written = process_pointer(f, va_arg(*ap, void *));
	else if (f->specifier == 'x' || f->specifier == 'X')
		written = process_hex(f, va_arg(*ap, unsigned int));
	else
		written = -1;
	free(f);
	return (written);
}

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
			f = ft_t_format_init();
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
