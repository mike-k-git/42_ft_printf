/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:45:49 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:45:14 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

ssize_t	print_padded_string(char *s, size_t len, size_t spaces, size_t start)
{
	ssize_t	written;

	if (start)
	{
		written = write(1, s, len);
		written += ft_putnchar(" ", spaces);
	}
	else
	{
		written = ft_putnchar(" ", spaces);
		written += write(1, s, len);
	}
	if (written == (ssize_t)(len + spaces))
		return (written);
	else
		return (-1);
}

/*
 *	printf("[%s]\n", s);	[(null)]
 *	printf("[%.s]\n", s);	[]
 *	printf("[%.0s]\n", s);	[]
 *	printf("[%.1s]\n", s);	[]
 *	printf("[%.2s]\n", s);	[]
 *	printf("[%.3s]\n", s);	[]
 *	printf("[%.4s]\n", s);	[]
 *	printf("[%.5s]\n", s);	[]
 *	printf("[%.6s]\n", s);	[(null)]
 */

char	*handle_null_string(t_format *f)
{
	if (!f->has_precision)
		return ("(null)");
	else if (f->precision > 5)
		return ("(null)");
	else
		return ("");
}

ssize_t	process_string(t_format *f, char *s)
{
	size_t	len;

	if (!s)
		s = handle_null_string(f);
	len = ft_strlen(s);
	if (f->has_precision == 1 && f->precision < len)
		len = f->precision;
	if (len == 0 && f->has_precision)
		return (ft_putnchar(" ", f->width));
	if (len >= f->width)
		return (write(1, s, len));
	else
	{
		f->pad_spaces = f->width - len;
		if (f->flag_minus == 1)
			return (print_padded_string(s, len, f->pad_spaces, 1));
		else
			return (print_padded_string(s, len, f->pad_spaces, 0));
	}
}
