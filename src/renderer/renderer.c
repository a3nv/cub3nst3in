/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:05:38 by iasonov           #+#    #+#             */
/*   Updated: 2025/04/24 00:09:52 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	render_next_frame(void *param)
{
	t_game	*g;
	int		x;

	g = (t_game *)param;
	if (g->key_w)
		move_dir(g, g->dir_x * g->move_speed,
			g->dir_y * g->move_speed);
	if (g->key_s)
		move_dir(g, -g->dir_x * g->move_speed,
			-g->dir_y * g->move_speed);
	if (g->key_a)
		move_dir(g, -g->plane_x * g->move_speed,
			-g->plane_y * g->move_speed);
	if (g->key_d)
		move_dir(g, g->plane_x * g->move_speed,
			g->plane_y * g->move_speed);
	if (g->key_left)
		rotate_player(g, -g->rot_speed);
	if (g->key_right)
		rotate_player(g, g->rot_speed);
	draw_floor_and_ceiling(g);
	x = 0;
	while (x < W_W)
	{
		cast_single_ray(g, x);
		x++;
	}
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->img_ptr, 0, 0);
	return (0);
}
