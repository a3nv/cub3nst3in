/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anon <anon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 00:05:38 by iasonov           #+#    #+#             */
/*   Updated: 2025/06/15 12:13:06 by anon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Helper function: retrieves the current time in seconds.
*/
double	get_time_in_seconds(void)
{
    struct timeval	tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

/*
** Calculate delta time since the last call.
** Returns the elapsed time in seconds. On the very first call, returns 0.
** multipiled by 100 for convenience
*/
double	delta_time(void)
{
    static double	last_time = 0.0;
    double			current_time;
    double			delta;

    current_time = get_time_in_seconds();
    if (last_time == 0.0)
        delta = 0.0;
    else
        delta = current_time - last_time;
    last_time = current_time;
    return (delta * 100);
}

static void	handle_movement(t_game *g)
{
	double dt;
	dt = delta_time();
	if (g->key_w)
		move_dir(g, g->dir_x * g->move_speed * dt, g->dir_y * g->move_speed * dt);
	if (g->key_s)
		move_dir(g, -g->dir_x * g->move_speed * dt, -g->dir_y * g->move_speed * dt);
	if (g->key_a)
		move_dir(g, -g->plane_x * g->move_speed * dt, -g->plane_y * g->move_speed * dt);
	if (g->key_d)
		move_dir(g, g->plane_x * g->move_speed * dt, g->plane_y * g->move_speed * dt);
	if (g->key_left)
		rotate_player(g, -g->rot_speed * dt);
	if (g->key_right)
		rotate_player(g, g->rot_speed * dt);
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
