/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:05:38 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/04 00:06:23 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	handle_movement(t_game *g)
{
	if (g->key_w)
		move_dir(g, g->dir_x * g->move_speed, g->dir_y * g->move_speed);
	if (g->key_s)
		move_dir(g, -g->dir_x * g->move_speed, -g->dir_y * g->move_speed);
	if (g->key_a)
		move_dir(g, -g->plane_x * g->move_speed, -g->plane_y * g->move_speed);
	if (g->key_d)
		move_dir(g, g->plane_x * g->move_speed, g->plane_y * g->move_speed);
	if (g->key_left)
		rotate_player(g, -g->rot_speed);
	if (g->key_right)
		rotate_player(g, g->rot_speed);
}

static void	render_scene(t_game *g)
{
	int	x;

	draw_floor_and_ceiling(g);
	x = 0;
	while (x < W_W)
	{
		cast_single_ray(g, x);
		x++;
	}
}

int	render_next_frame(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	if (!g->running)
		return (0);
	handle_movement(g);
	render_scene(g);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 0, 0);
	return (0);
}
