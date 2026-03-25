/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:44:09 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:45:53 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

ssize_t	print_padded_char(unsigned char c, size_t spaces, size_t start)
{
	ssize_t	written;

	if (start)
	{
		written = write(1, &c, 1);
		written += ft_putnchar(" ", spaces);
	}
	else
	{
		written = ft_putnchar(" ", spaces);
		written += write(1, &c, 1);
	}
	if (written == (ssize_t)(1 + spaces))
		return (written);
	else
		return (-1);
}

ssize_t	process_char(t_format *f, int c)
{
	unsigned char	out;

	out = (unsigned char)c;
	if (f->width > 1)
	{
		f->pad_spaces = f->width - 1;
		if (f->flag_minus == 1)
			return (print_padded_char(out, f->pad_spaces, 1));
		else
			return (print_padded_char(out, f->pad_spaces, 0));
	}
	else
		return (write(1, &out, 1));
}
