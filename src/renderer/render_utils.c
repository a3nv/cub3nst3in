/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:48:13 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/01 22:48:15 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Global pixel-putter so both floor/ceiling and wall-draw can use it
*/
void	put_pixel(t_game *g, int x, int y, int color)
{
	char	*dst;

	dst = g->img_data + (y * g->line_len + x * (g->bpp / 8));
	*(unsigned int *)dst = color;
}

/*
** Fill the top half with ceiling, bottom half with floor
*/
void	draw_floor_and_ceiling(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < W_H)
	{
		x = 0;
		while (x < W_W)
		{
			if (y < W_H / 2)
				put_pixel(g, x, y, g->ceiling->hex);
			else
				put_pixel(g, x, y, g->floor->hex);
			x++;
		}
		y++;
	}
}
