/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:54:45 by bjacobs           #+#    #+#             */
/*   Updated: 2022/12/02 11:47:53 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_baselen(unsigned long long n, int base)
{
	size_t	len;

	len = 1;
	while (n > (unsigned long long)(base - 1))
	{
		n /= base;
		len++;
	}
	return (len);
}

char	*ft_btoa(char *s, unsigned long long n, int base, size_t len)
{
	unsigned long long	rem;

	s[len] = '\0';
	while (len--)
	{
		rem = n % base;
		if (rem > 9)
			s[len] = rem + 'a' - 10;
		else
			s[len] = rem + '0';
		n /= base;
	}
	return (s);
}
