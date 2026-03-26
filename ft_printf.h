/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 16:17:50 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:58:51 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <sys/types.h>
# include <stdarg.h>

typedef struct s_format
{
	char	specifier;
	size_t	width;
	size_t	has_precision;
	size_t	precision;
	size_t	flag_minus;
	size_t	flag_zero;
	size_t	flag_blank;
	size_t	flag_plus;
	size_t	flag_hash;
	size_t	pad_zeroes;
	size_t	pad_spaces;
	int		fd;
	char	*prefix;
}	t_format;

int			ft_printf(const char *fmt, ...);
int			ft_dprintf(int fd, const char *fmt, ...);
ssize_t		ft_putnchar_fd(char *c, size_t n, int fd);
t_format	*ft_t_format_init(int fd);
int			ft_isflag(char c);
int			ft_isformat_specifier(char c);
void		set_flag(const char **fmt, t_format *f);
int			parse_format_specifier(const char **fmt, t_format *f);
void		set_prefix(t_format *f, long arg);
ssize_t		process_hex(t_format *f, unsigned int arg);
ssize_t		process_percent(t_format *f);
ssize_t		process_string(t_format *f, char *s);
ssize_t		process_char(t_format *f, int c);
ssize_t		process_int(t_format *f, int arg);
ssize_t		process_pointer(t_format *f, void *arg);
ssize_t		process_uint(t_format *f, unsigned int arg);
ssize_t		convert_specifier(va_list *ap, t_format *f);

#endif 
