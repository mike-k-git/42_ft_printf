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

ssize_t	print_padded_char(unsigned char c, size_t spaces, size_t start, int fd)
{
	ssize_t	written;

	if (start)
	{
		written = write(fd, &c, 1);
		written += ft_putnchar_fd(" ", spaces, fd);
	}
	else
	{
		written = ft_putnchar_fd(" ", spaces, fd);
		written += write(fd, &c, 1);
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
			return (print_padded_char(out, f->pad_spaces, 1, f->fd));
		else
			return (print_padded_char(out, f->pad_spaces, 0, f->fd));
	}
	else
		return (write(f->fd, &out, 1));
}
