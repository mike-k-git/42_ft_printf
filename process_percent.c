/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_percent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkugan <mkugan@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:34:12 by mkugan            #+#    #+#             */
/*   Updated: 2025/06/01 16:44:48 by mkugan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

ssize_t	process_percent(t_format *f)
{
	return (write(f->fd, "%", 1));
}
