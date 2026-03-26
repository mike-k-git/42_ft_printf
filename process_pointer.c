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
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

size_t	print_padded_null(char *ptr, size_t len, t_format *f, size_t start)
{
	ssize_t	written;

	if (start)
	{
		written = write(f->fd, ptr, len);
		written += ft_putnchar_fd(" ", f->width - len, f->fd);
	}
	else
	{
		written = ft_putnchar_fd(" ", f->width - len, f->fd);
		written += write(f->fd, ptr, len);
	}
	if (written == (ssize_t)(f->width))
		return (written);
	return (-1);
}

ssize_t	print_padded_pointer(char **ptr, size_t len, t_format *f, size_t start)
{
	ssize_t	written;

	if (start)
	{
		written = write(f->fd, "0x", 2);
		written += write(f->fd, *ptr, len);
		written += ft_putnchar_fd(" ", f->width - len - 2, f->fd);
	}
	else
	{
		written = ft_putnchar_fd(" ", f->width - len - 2, f->fd);
		written += write(f->fd, "0x", 2);
		written += write(f->fd, *ptr, len);
	}
	free(*ptr);
	if (written == (ssize_t)(f->width))
		return (written);
	return (-1);
}

ssize_t	print_pointer(char **ptr, size_t len, t_format *f)
{
	ssize_t	written;

	written = write(f->fd, "0x", 2);
	written += write(f->fd, *ptr, len);
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
			return (print_padded_null(ptr, 5, f, 1));
		else
			return (print_padded_null(ptr, 5, f, 0));
	}
	return (write(f->fd, ptr, 5));
}

ssize_t	process_pointer(t_format *f, void *arg)
{
	char	*ptr;
	size_t	len;

	if (arg == NULL)
		return (handle_null_pointer(f));
	ptr = ft_ultoa_base((unsigned long)arg, "0123456789abcdef");
	len = ft_strlen(ptr);
	if (f->width > len + 2)
	{
		if (f->flag_minus == 1)
			return (print_padded_pointer(&ptr, len, f, 1));
		else
			return (print_padded_pointer(&ptr, len, f, 0));
	}
	else
		return (print_pointer(&ptr, len, f));
}
