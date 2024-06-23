/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:38:32 by bjacobs           #+#    #+#             */
/*   Updated: 2022/12/02 12:17:33 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstl;
	size_t	srcl;

	i = 0;
	dstl = ft_strlen(dst);
	srcl = ft_strlen(src);
	if (dstl > dstsize)
		return (srcl + dstsize);
	while (src[i] && i + dstl + 1 < dstsize)
	{
		dst[dstl + i] = src[i];
		i++;
	}
	if (dstl + i < dstsize)
		dst[dstl + i] = '\0';
	return (srcl + dstl);
}
