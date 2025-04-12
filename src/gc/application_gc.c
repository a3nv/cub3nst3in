/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   application_gc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:43:49 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/09 23:52:42 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_map(char **map, int height)
{
	int	i;

	if (map == NULL)
		return ;
	i = 0;
	while (i < height)
	{
		if (map[i] != NULL)
		{
			free(map[i]);
			map[i] = NULL;
		}
		i++;
	}
	free(map);
	map = NULL;
}
