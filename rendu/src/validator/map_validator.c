/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 20:55:55 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/27 20:57:11 by iasonov          ###   ########.fr       */
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
				printf("Invalid character in map: %c\n", c);
				g->error_message = "Error: Invalid character in map\n";
				g->status = E;
				return (false);
			}
			col++;
		}
		row++;
	}
	return (true);
}

bool	check_cell(int row, int col, t_game *g)
{
	return (get_cell(g, row - 1, col) == ' '
		|| get_cell(g, row + 1, col) == ' '
		|| get_cell(g, row, col - 1) == ' '
		|| get_cell(g, row, col + 1) == ' ');
}

bool	check_enclosure(t_game *g)
{
	int		row;
	int		col;

	row = 0;
	while (g->map->data[row])
	{
		col = 0;
		while (get_cell(g, row, col) != '\n' && get_cell(g, row, col) != '\0')
		{
			if (get_cell(g, row, col) != '1' && get_cell(g, row, col) != ' ')
			{
				if (check_cell(row, col, g))
				{
					g->error_message = "Error: Map is not closed by walls\n";
					g->status = E;
					return (false);
				}
			}
			col++;
		}
		row++;
	}
	return (true);
}

bool	is_map_valid(t_game *g)
{
	if (g->status != E && !validate_chars_and_player(g))
		return (false);
	if (g->status != E && g->player_counter != 1)
	{
		g->status = E;
		g->error_message = "Error: Invalid number of players\n";
		return (false);
	}
	if (g->status != E && !check_enclosure(g))
		return (false);
	if (g->status != E && (g->floor == NULL || g->ceiling == NULL))
	{
		g->status = E;
		g->error_message = ft_strdup("Error: F/C colors missing\n");
		return (false);
	}
	return (true);
}
