/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:51:22 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:53:46 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

ssize_t	handle_zero_with_zero_precision(t_format *f)
{
	if (f->width > 0)
		return (ft_putnchar_fd(" ", f->width, f->fd));
	return (0);
}

char	*set_digits(t_format *f, unsigned int arg)
{
	char	*digits;

	if (f->specifier == 'x')
		digits = ft_ultoa_base((unsigned long)arg, "0123456789abcdef");
	else
		digits = ft_ultoa_base((unsigned long)arg, "0123456789ABCDEF");
	return (digits);
}

ssize_t	print_hex_padded_left_aligned(t_format *f, char *digits, size_t len)
{
	ssize_t	written;
	size_t	len_prefix;

	len_prefix = ft_strlen(f->prefix);
	written = write(f->fd, f->prefix, len_prefix);
	written += ft_putnchar_fd("0", f->pad_zeroes, f->fd);
	written += write(f->fd, digits, len);
	written += ft_putnchar_fd(" ", f->pad_spaces, f->fd);
	free(digits);
	if (written == (ssize_t)(f->pad_zeroes + len + f->pad_spaces + len_prefix))
		return (written);
	return (-1);
}

ssize_t	print_hex_padded_right_aligned(t_format *f, char *digits, size_t len)
{
	ssize_t	written;
	size_t	len_prefix;

	len_prefix = ft_strlen(f->prefix);
	if (f->flag_zero && !f->has_precision)
	{
		written = write(f->fd, f->prefix, len_prefix);
		written += ft_putnchar_fd("0", f->pad_spaces, f->fd);
	}
	else
	{
		written = ft_putnchar_fd(" ", f->pad_spaces, f->fd);
		written += write(f->fd, f->prefix, len_prefix);
	}
	written += ft_putnchar_fd("0", f->pad_zeroes, f->fd);
	written += write(f->fd, digits, len);
	free(digits);
	if (written == (ssize_t)(f->pad_zeroes + len + f->pad_spaces + len_prefix))
		return (written);
	return (-1);
}

ssize_t	process_hex(t_format *f, unsigned int arg)
{
	char	*digits;
	size_t	len;
	ssize_t	len_prefix;

	if (arg == 0 && f->has_precision && f->precision == 0)
		return (handle_zero_with_zero_precision(f));
	set_prefix(f, (long)arg);
	digits = set_digits(f, arg);
	len = ft_strlen(digits);
	len_prefix = ft_strlen(f->prefix);
	if (f->has_precision && f->precision > len)
		f->pad_zeroes = f->precision - len;
	if (f->width > len + f->pad_zeroes + len_prefix)
		f->pad_spaces = f->width - len - f->pad_zeroes - len_prefix;
	if (f->flag_minus)
		return (print_hex_padded_left_aligned(f, digits, len));
	return (print_hex_padded_right_aligned(f, digits, len));
}
