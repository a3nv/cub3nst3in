/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:55:55 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/14 22:27:11 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	get_cell(t_game *g, int r, int c)
{
	if (r < 0 || !g->map->data[r])
		return ('\0');
	if (c < 0 || c >= (int)ft_strlen(g->map->data[r]))
		return ('\0');
	return (g->map->data[r][c]);
}

bool	validate_chars_and_player(t_game *g)
{
	int		row;
	int		col;
	char	c;

	row = 0;
	while (g->map->data[row])
	{
		col = 0;
		while (get_cell(g, row, col) != '\0')
		{
			c = get_cell(g, row, col);
			if (c != '0' && c != '1' && !is_player(c) && c != ' ' && c != '\n')
			{
				set_em(g, "Error: Invalid character in map\n", E);
				return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}

bool	is_map_valid(t_game *g)
{
	if (g->status == E)
		return (false);
	if (g->player_counter != 1)
	{
		set_em(g, "Error: Invalid number of players\n", E);
		return (false);
	}
	if (g->floor == NULL || g->ceiling == NULL)
	{
		set_em(g, "Error: F/C colors missing\n", E);
		return (false);
	}
	if (g->no_ptr == NULL || g->so_ptr == NULL || g->we_ptr == NULL
		|| g->ea_ptr == NULL)
	{
		set_em(g, "Error: Texture is missing\n", E);
		return (false);
	}
	if (!validate_chars_and_player(g))
		return (false);
	if (!check_enclosure(g))
		return (false);
	return (true);
}
