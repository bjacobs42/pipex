/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacobs <bjacobs@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:45:32 by bjacobs           #+#    #+#             */
/*   Updated: 2022/12/02 12:26:27 by bjacobs          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

/*int main(void)
{
	int	test[] = {1, 4, 5, 121312313};
	t_list *n = ft_lstnew(test);
	int	*decimal;

	decimal = (int *)n->content;
	int i = 0;
	while (i < 4)
	{
		printf("%d\n", decimal[i]);
		i++;
	}
	if (n->next == NULL)
		printf("null\n");
	else
		printf("true\n");
	free(n);
	return (0);
} */
