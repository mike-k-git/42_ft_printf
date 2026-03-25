/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_unsigned_int.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 16:50:49 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:57:39 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdlib.h>

ssize_t	print_uint_padded_left_aligned(t_format *f, char *output, size_t len)
{
	ssize_t	written;

	written = ft_putnchar("0", f->pad_zeroes);
	written += write(1, output, len);
	written += ft_putnchar(" ", f->pad_spaces);
	free(output);
	if (written == (ssize_t)(f->pad_zeroes + len + f->pad_spaces))
		return (written);
	return (-1);
}

ssize_t	print_uint_padded_right_aligned(t_format *f, char *output, size_t len)
{
	ssize_t	written;

	if (f->flag_zero && !f->has_precision)
		written = ft_putnchar("0", f->pad_spaces);
	else
		written = ft_putnchar(" ", f->pad_spaces);
	written += ft_putnchar("0", f->pad_zeroes);
	written += write(1, output, len);
	free(output);
	if (written == (ssize_t)(f->pad_zeroes + len + f->pad_spaces))
		return (written);
	return (-1);
}

ssize_t	process_uint(t_format *f, unsigned int arg)
{
	char	*output;
	size_t	len;

	if (arg == 0 && f->has_precision && f->precision == 0)
		output = ft_strdup("");
	else
		output = ft_itoa_long((unsigned long)arg);
	len = ft_strlen(output);
	if (f->has_precision && f->precision > len)
		f->pad_zeroes = f->precision - len;
	if (f->width > len + f->pad_zeroes)
		f->pad_spaces = f->width - len - f->pad_zeroes;
	if (f->flag_minus)
		return (print_uint_padded_left_aligned(f, output, len));
	return (print_uint_padded_right_aligned(f, output, len));
}
