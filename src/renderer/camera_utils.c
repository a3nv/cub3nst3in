/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iasonov <iasonov@student.42prague.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 00:04:47 by iasonov           #+#    #+#             */
/*   Updated: 2025/05/04 00:04:49 by iasonov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_camera_pos(t_game *g)
{
	if (g->start_dir == 'N')
	{
		g->dir_y = -1;
		g->plane_x = 0.66;
	}
	else if (g->start_dir == 'S')
	{
		g->dir_y = 1;
		g->plane_x = -0.66;
	}
	else if (g->start_dir == 'E')
	{
		g->dir_x = 1;
		g->plane_y = 0.66;
	}
	else if (g->start_dir == 'W')
	{
		g->dir_x = -1;
		g->plane_y = -0.66;
	}
}

void	init_camera(t_game *g)
{
	g->dir_x = 0;
	g->dir_y = 0;
	g->plane_x = 0;
	g->plane_y = 0;
	init_camera_pos(g);
	g->move_speed = 0.05;
	g->rot_speed = 0.03;
}
