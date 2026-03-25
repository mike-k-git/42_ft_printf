/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:35:30 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 17:49:36 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

ssize_t	print_padded_null(char *ptr, size_t len, size_t width, size_t start)
{
	ssize_t	written;

	if (start)
	{
		written = write(1, ptr, len);
		written += ft_putnchar(" ", width - len);
	}
	else
	{
		written = ft_putnchar(" ", width - len);
		written += write(1, ptr, len);
	}
	if (written == (ssize_t)(width))
		return (written);
	return (-1);
}

ssize_t	print_padded_pointer(char **ptr, size_t len, size_t width, size_t start)
{
	ssize_t	written;

	if (start)
	{
		written = write(1, "0x", 2);
		written += write(1, *ptr, len);
		written += ft_putnchar(" ", width - len - 2);
	}
	else
	{
		written = ft_putnchar(" ", width - len - 2);
		written += write(1, "0x", 2);
		written += write(1, *ptr, len);
	}
	free(*ptr);
	if (written == (ssize_t)(width))
		return (written);
	return (-1);
}

ssize_t	print_pointer(char **ptr, size_t len)
{
	ssize_t	written;

	written = write(1, "0x", 2);
	written += write(1, *ptr, len);
	free(*ptr);
	if (written == (ssize_t)(len + 2))
		return (written);
	return (-1);
}

ssize_t	handle_null_pointer(t_format *f)
{
	char	*ptr;

	ptr = "(nil)";
	if (f->width > 5)
	{
		if (f->flag_minus)
			return (print_padded_null(ptr, 5, f->width, 1));
		else
			return (print_padded_null(ptr, 5, f->width, 0));
	}
	return (write(1, ptr, 5));
}

ssize_t	process_pointer(t_format *f, void *arg)
{
	char	*ptr;
	size_t	len;

	if (arg == NULL)
		return (handle_null_pointer(f));
	ptr = ft_utoa_base((unsigned long)arg, "0123456789abcdef");
	len = ft_strlen(ptr);
	if (f->width > len + 2)
	{
		if (f->flag_minus == 1)
			return (print_padded_pointer(&ptr, len, f->width, 1));
		else
			return (print_padded_pointer(&ptr, len, f->width, 0));
	}
	else
		return (print_pointer(&ptr, len));
}
