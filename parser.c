/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 11:45:28 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:29:01 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_atoi_advance(const char **fmt)
{
	size_t	width;

	width = 0;
	while (**fmt >= '0' && **fmt <= '9')
	{
		width = width * 10 + (**fmt - '0');
		(*fmt)++;
	}
	return (width);
}

int	ft_isflag(char c)
{
	if (c == '0' || c == ' ' || c == '+' || c == '#' || c == '-')
		return (1);
	return (0);
}

int	ft_isformat_specifier(char c)
{
	if (c == 'd' || c == 'i' || c == 'c' || c == 's' || c == 'p'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	return (0);
}

void	set_flag(const char **fmt, t_format *f)
{
	if (**fmt == '0')
		f->flag_zero = 1;
	else if (**fmt == ' ')
		f->flag_blank = 1;
	else if (**fmt == '+')
		f->flag_plus = 1;
	else if (**fmt == '#')
		f->flag_hash = 1;
	else if (**fmt == '-')
		f->flag_minus = 1;
	(*fmt)++;
}

int	parse_format_specifier(const char **fmt, t_format *f)
{
	while (ft_isflag(**fmt) == 1)
		set_flag(fmt, f);
	if (**fmt >= '1' && **fmt <= '9')
		f->width = ft_atoi_advance(fmt);
	if (**fmt == '.')
	{
		(*fmt)++;
		f->has_precision = 1;
		f->precision = ft_atoi_advance(fmt);
	}
	if (ft_isformat_specifier(**fmt) == 1)
	{
		f->specifier = **fmt;
		(*fmt)++;
		return (0);
	}
	else
	{
		f->specifier = '\0';
		return (-1);
	}
}
