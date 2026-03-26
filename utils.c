/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:42:24 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:07:45 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

ssize_t	ft_putnchar_fd(char *c, size_t n, int fd)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (write(fd, c, 1) == -1)
			return (-1);
		i++;
	}
	return (n);
}

t_format	*ft_t_format_init(int fd)
{
	t_format	*f;

	f = malloc(sizeof(t_format));
	if (!f)
		return (NULL);
	f->specifier = 0;
	f->width = 0;
	f->has_precision = 0;
	f->precision = 0;
	f->flag_zero = 0;
	f->flag_plus = 0;
	f->flag_minus = 0;
	f->flag_blank = 0;
	f->flag_hash = 0;
	f->pad_zeroes = 0;
	f->pad_spaces = 0;
	f->fd = fd;
	f->prefix = NULL;
	return (f);
}

void	set_prefix(t_format *f, long arg)
{
	if (f->specifier == 'x' && arg != 0 && f->flag_hash)
		f->prefix = "0x";
	else if (f->specifier == 'X' && arg != 0 && f->flag_hash)
		f->prefix = "0X";
	else if (arg >= 0)
	{
		if (f->flag_plus)
			f->prefix = "+";
		else if (f->flag_blank)
			f->prefix = " ";
		else
			f->prefix = "";
	}
	else
		f->prefix = "-";
}

char	*ft_strdup(char *s)
{
	char	*new;
	size_t	s_len;
	size_t	i;

	s_len = ft_strlen(s);
	new = (char *)malloc(sizeof(char) * s_len + 1);
	if (!new)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

size_t	ft_strlen(char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

ssize_t	convert_specifier(va_list *ap, t_format *f)
{
	ssize_t	written;

	if (f->specifier == '%')
		written = process_percent(f);
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

static int	ft_size_n(long n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n / 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(long n)
{
	char	*num;
	int		len;
	int		is_negative;

	is_negative = 0;
	len = ft_size_n(n);
	if (n < 0)
		is_negative = 1;
	num = (char *)malloc(sizeof(char) * (len + 1));
	if (!num)
		return (NULL);
	num[len] = '\0';
	while (len--)
	{
		if (n % 10 < 0)
			num[len] = -(n % 10) + '0';
		else
			num[len] = (n % 10) + '0';
		n /= 10;
		if (len == 0 && is_negative)
			num[len] = '-';
	}
	return (num);
}
