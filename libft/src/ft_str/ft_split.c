/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 17:38:14 by bjacobs           #+#    #+#             */
/*   Updated: 2022/12/08 16:27:35 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	arr_size(char const *s, char c)
{
	size_t	i;
	size_t	arrsize;

	i = 0;
	arrsize = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			arrsize++;
		}
		else
			i++;
	}
	return (arrsize);
}

void	ft_clear_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static char	**create_arr(char const *s, char c, char **array)
{
	size_t	i;
	size_t	start;
	size_t	arr_i;

	i = 0;
	start = 0;
	arr_i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			array[arr_i] = ft_substr(s, start, i - start);
			if (!array[arr_i])
				return (ft_clear_arr(array), NULL);
			arr_i++;
		}
		else
			i++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	size_t	arr_s;
	char	**array;

	arr_s = arr_size(s, c);
	array = (char **)ft_calloc(sizeof(char *), arr_s + 1);
	if (!array)
		return (NULL);
	if (!create_arr(s, c, array))
		return (NULL);
	return (array);
}
