/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 16:51:33 by bjacobs           #+#    #+#             */
/*   Updated: 2022/12/10 11:54:02 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_fd.h"
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

static int	print_arg(char c, va_list ap, int fd)
{
	if (c == 'c')
		return (print_c((char)va_arg(ap, int), fd));
	else if (c == 's')
		return (print_s(va_arg(ap, char *), fd));
	else if (c == 'd' || c == 'i')
		return (print_d(va_arg(ap, int), fd));
	else if (c == 'x' || c == 'X')
		return (print_x(va_arg(ap, unsigned int), c, fd));
	else if (c == 'u')
		return (print_u(va_arg(ap, unsigned int), fd));
	else if (c == 'p')
		return (print_p(va_arg(ap, uintptr_t), fd));
	else if ('%')
		return (print_c(c, fd));
	return (0);
}

static int	print_fmt_s(const char *fmt, int fd)
{
	int	i;

	i = 0;
	while (fmt[i] != '%' && fmt[i])
		i++;
	if (write(fd, fmt, sizeof(char) * i) < 0)
		return (-1);
	return (i);
}

static int	iterate_fmt(const char *fmt, va_list ap, int *chars, int fd)
{
	int	i;
	int	check;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%')
		{
			check = print_fmt_s(&fmt[i], fd);
			i += check;
		}
		else if (fmt[++i])
		{
			check = print_arg(fmt[i], ap, fd);
			i++;
		}
		if (check < 0)
			return (check);
		*chars += check;
	}
	return (1);
}

int	ft_printf_fd(const char *fmt, int fd, ...)
{
	va_list	ap;
	int		characters;
	int		check;

	va_start(ap, fd);
	characters = 0;
	check = iterate_fmt(fmt, ap, &characters, fd);
	va_end(ap);
	if (check < 0)
		return (check);
	return (characters);
}
