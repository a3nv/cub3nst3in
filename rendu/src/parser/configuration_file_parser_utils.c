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
	array_list_add(g->map, l);
}

bool	find_player_start(t_game *g, char *l, int row)
{
	int	col;

	col = 0;
	while (l[col])
	{
		if (is_player(l[col]))
		{
			g->player_counter++;
			g->player_x = col;
			g->player_y = row;
			g->start_dir = l[col];
			g->pos_x = col + 0.5;
			g->pos_y = row + 0.5;
			g->map->data[row][col] = '0';
		}
		col++;
	}
	return (true);
}
