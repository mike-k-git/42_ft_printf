/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_signed_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:33:00 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:48:49 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

ssize_t	print_int_padded_left_aligned(t_format *f, char *output, size_t len)
{
	ssize_t	written;
	size_t	len_prefix;

	len_prefix = ft_strlen(f->prefix);
	written = write(f->fd, f->prefix, len_prefix);
	written += ft_putnchar_fd("0", f->pad_zeroes, f->fd);
	written += write(f->fd, output, len);
	written += ft_putnchar_fd(" ", f->pad_spaces, f->fd);
	free(output);
	if (written == (ssize_t)(f->pad_zeroes + len + f->pad_spaces + len_prefix))
		return (written);
	return (-1);
}

ssize_t	print_int_padded_right_aligned(t_format *f, char *output, size_t len)
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
	written += write(f->fd, output, len);
	free(output);
	if (written == (ssize_t)(f->pad_zeroes + len + f->pad_spaces + len_prefix))
		return (written);
	return (-1);
}

ssize_t	process_int(t_format *f, int arg)
{
	long	num;
	char	*output;
	size_t	len;
	size_t	len_prefix;

	num = (long)arg;
	if (num < 0)
		num = -num;
	set_prefix(f, (long)arg);
	if (arg == 0 && f->has_precision && f->precision == 0)
		output = ft_strdup("");
	else
		output = ft_itoa(num);
	if (!output)
		return (-1);
	len = ft_strlen(output);
	len_prefix = ft_strlen(f->prefix);
	if (f->has_precision && f->precision > len)
		f->pad_zeroes = f->precision - len;
	if (f->width > len + f->pad_zeroes + len_prefix)
		f->pad_spaces = f->width - len - f->pad_zeroes - len_prefix;
	if (f->flag_minus)
		return (print_int_padded_left_aligned(f, output, len));
	else
		return (print_int_padded_right_aligned(f, output, len));
}
