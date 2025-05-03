/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configuration_file_parser_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:09:40 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/04 00:09:41 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	add_line_to_map(t_game *g, char *l)
{
	if (!is_map_line(l))
		error_exit("Error\nInvalid map line encountered\n", g);
	array_list_add(g->map, l);
}

void	find_player_start(t_game *g, char *l, int row)
{
	int	col;

	col = 0;
	while (l[col])
	{
		if (l[col] == 'N' || l[col] == 'S'
			|| l[col] == 'E' || l[col] == 'W')
		{
			g->player_x = col;
			g->player_y = row;
			g->start_dir = l[col];
			g->pos_x = col + 0.5;
			g->pos_y = row + 0.5;
			g->map->data[row][col] = '0';
		}
		col++;
	}
}
