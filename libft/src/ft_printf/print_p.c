/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:12:07 by bjacobs           #+#    #+#             */
/*   Updated: 2022/12/10 11:54:24 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_printf_fd.h"
#include <stdlib.h>

int	print_p(unsigned long long n, int fd)
{
	int		characters;
	size_t	len;
	char	*s;

	len = ft_baselen(n, 16);
	s = (char *)malloc(sizeof(char) * len + 3);
	if (!s)
		return (-1);
	ft_memcpy(s, "0x", 2);
	ft_btoa(s + 2, n, 16, len);
	characters = print_s(s, fd);
	return (free(s), characters);
}
