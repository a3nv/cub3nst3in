/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 22:47:33 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/01 22:47:37 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Initialize ray pos/dir and delta distances
*/
void	init_ray(t_game *g, int x, t_ray *r)
{
	r->camera_x = 2 * x / (double) W_W - 1;
	r->ray_dir_x = g->dir_x + g->plane_x * r->camera_x;
	r->ray_dir_y = g->dir_y + g->plane_y * r->camera_x;
	r->map_x = g->pos_x;
	r->map_y = g->pos_y;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
}

/*
** Compute slice dimensions, draw limits, and texture X-coord
*/
void	compute_draw_parameters(t_game *g, t_ray *r)
{
	double	wall_x;

	r->line_height = (int)(W_H / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + W_H / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + W_H / 2;
	if (r->draw_end >= W_H)
		r->draw_end = W_H - 1;
	if (r->side == 0)
		wall_x = g->pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = g->pos_x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	r->tex_x = (int)(wall_x * g->tex_w[r->tex_num]);
	if ((r->side == 0 && r->ray_dir_x > 0)
		|| (r->side == 1 && r->ray_dir_y < 0))
		r->tex_x = g->tex_w[r->tex_num] - r->tex_x - 1;
}

/*
** Draw the vertical slice from draw_start to draw_end
*/
void	draw_wall_slice(t_game *g, int x, t_ray *r)
{
	int		y;
	double	step;
	double	tex_pos;
	int		tex_y;
	int		pix_i;

	step = (double)g->tex_h[r->tex_num] / r->line_height;
	tex_pos = (r->draw_start - W_H / 2 + r->line_height / 2) * step;
	y = r->draw_start;
	while (y < r->draw_end)
	{
		tex_y = (int)tex_pos & (g->tex_h[r->tex_num] - 1);
		tex_pos += step;
		pix_i = (tex_y * g->tex_w[r->tex_num] + r->tex_x) * (g->bpp / 8);
		put_pixel(g, x, y, *(unsigned int *)
			(g->tex_data[r->tex_num] + pix_i));
		y++;
	}
}

/*
** Cast one ray column and draw it
*/
void	cast_single_ray(t_game *g, int x)
{
	t_ray	r;

	init_ray(g, x, &r);
	do_dda(g, &r);
	compute_draw_parameters(g, &r);
	draw_wall_slice(g, x, &r);
}
