/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:01:46 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/04 00:01:47 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_step_and_sidedist(t_game *g, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (g->pos_x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - g->pos_x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (g->pos_y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - g->pos_y) * r->delta_dist_y;
	}
}

static void	perform_dda(t_game *g, t_ray *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (g->map->data[r->map_y][r->map_x] != '0')
			hit = 1;
	}
}

void	do_dda(t_game *g, t_ray *r)
{
	init_step_and_sidedist(g, r);
	perform_dda(g, r);
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->pos_x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->pos_y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			r->tex_num = TEX_WE;
		else
			r->tex_num = TEX_EA;
	}
	else
	{
		if (r->ray_dir_y > 0)
			r->tex_num = TEX_NO;
		else
			r->tex_num = TEX_SO;
	}
}
