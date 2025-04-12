/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:49:40 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/13 00:25:55 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	count_height(t_game *game)
{
	int	i;

	i = 0;
	while (game->map->data[i])
		i++;
	return (i);
}

void	set_map_dimensions(t_game *game)
{
	int	height;
	int	width;

	height = count_height(game);
	game->map_height = height;
	if (height > 0)
		width = ft_strlen(game->map->data[0]);
	else
		width = 0;
	game->map_width = width;
}
