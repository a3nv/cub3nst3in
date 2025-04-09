/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pair.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 00:33:00 by iasonov           #+#    #+#             */
/*   Updated: 2025/01/05 18:14:52 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_pair	*create_pair(char *first, char *second)
{
	t_pair	*pair;

	if (!first || !second)
		return (NULL);
	pair = (t_pair *) malloc(sizeof(t_pair));
	if (!pair)
		return (NULL);
	pair->first = first;
	pair->second = second;
	return (pair);
}

void	free_pair(t_pair *pair)
{
	free(pair->first);
	free(pair->second);
	free(pair);
}
