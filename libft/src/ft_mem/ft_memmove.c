/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:37:49 by bjacobs           #+#    #+#             */
/*   Updated: 2022/10/27 16:24:02 by bjacobs       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*dp;
	unsigned char	*sp;

	dp = (unsigned char *)dst;
	sp = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	if (dp > sp)
	{
		while (n--)
			dp[n] = sp[n];
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
